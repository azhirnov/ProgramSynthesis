// Copyright (c)  Zhirnov Andrey. For more information see 'LICENSE.txt'

#include "Common.h"
#include "Engine/Platforms/Public/Tools/GPUThreadHelper.h"
#include "all_pipelines.h"

namespace CodeGen
{

	extern bool Test_GpuBigInt ()
	{
		// create resources
		auto		factory		= GetMainSystemInstance()->GlobalSystems()->modulesFactory;
		
		ModulePtr	gpu_thread	= PlatformTools::GPUThreadHelper::FindComputeThread( factory->GlobalSystems() );
		CHECK_ERR( gpu_thread );
		
		GpuMsg::GetGraphicsModules	req_ids;
		gpu_thread->Send( req_ids );
		ComputeModuleIDs	gpuIDs = *req_ids.compute;

		ModulePtr	sync_manager = gpu_thread->GetModuleByMsg<CompileTime::TypeListFrom< GpuMsg::CreateFence >>();
		CHECK_ERR( sync_manager );

		GpuMsg::CreateFence		fence_ctor;
		sync_manager->Send( fence_ctor );
		
		ModulePtr	cmd_builder;
		CHECK_ERR( factory->Create(
						gpuIDs.commandBuilder,
						gpu_thread->GlobalSystems(),
						CreateInfo::GpuCommandBuilder{},
						OUT cmd_builder ) );

		ModulePtr	cmd_buffer;
		CHECK_ERR( factory->Create(
						gpuIDs.commandBuffer,
						gpu_thread->GlobalSystems(),
						CreateInfo::GpuCommandBuffer{},
						OUT cmd_buffer ) );
		cmd_builder->Send( ModuleMsg::AttachModule{ cmd_buffer });

		ModulePtr	buffer;
		CHECK_ERR( factory->Create(
						gpuIDs.buffer,
						gpu_thread->GlobalSystems(),
						CreateInfo::GpuBuffer{
							BufferDescription{ 16_b, EBufferUsage::Storage },
							EGpuMemory::CoherentWithCPU },
						OUT buffer ) );

		CreateInfo::PipelineTemplate	pt_ci;
		Pipelines::Create_biginttest( OUT pt_ci.descr );
	
		ModulePtr	pipeline_template;
		CHECK_ERR( factory->Create(
						PipelineTemplateModuleID,
						gpu_thread->GlobalSystems(),
						pt_ci,
						OUT pipeline_template ) );
		ModuleUtils::Initialize({ pipeline_template });

		GpuMsg::CreateComputePipeline	cppl_ctor{ gpuIDs.pipeline, gpu_thread };
		pipeline_template->Send( cppl_ctor );

		ModulePtr	pipeline	= *cppl_ctor.result;
		ModulePtr	resource_table;
		CHECK_ERR( factory->Create(
						gpuIDs.resourceTable,
						gpu_thread->GlobalSystems(),
						CreateInfo::PipelineResourceTable{},
						OUT resource_table ) );
	
		resource_table->Send( ModuleMsg::AttachModule{ "pipeline", pipeline });
		resource_table->Send( ModuleMsg::AttachModule{ "ssb", buffer });

		ModuleUtils::Initialize({ cmd_builder, cmd_buffer, buffer, pipeline, resource_table });


		// build command buffer
		cmd_builder->Send( GpuMsg::CmdBegin{ cmd_buffer });

		cmd_builder->Send( GpuMsg::CmdBindComputePipeline{ pipeline });
		cmd_builder->Send( GpuMsg::CmdBindComputeResourceTable{ resource_table });
		cmd_builder->Send( GpuMsg::CmdDispatch{ uint3(1) });
	
		GpuMsg::CmdEnd	cmd_end;
		cmd_builder->Send( cmd_end );


		// submit and sync
		gpu_thread->Send( GpuMsg::SubmitComputeQueueCommands{ *cmd_end.result, *fence_ctor.result });

		sync_manager->Send( GpuMsg::ClientWaitFence{ *fence_ctor.result });


		// read from buffer
		uint	result = 0;

		GpuMsg::ReadFromGpuMemory	read_cmd{ BinArrayRef::FromValue( result ) };
		buffer->Send( read_cmd );

		CHECK_FATAL( result == 111 );

		LOG( "Test_GpuBigInt - OK", ELog::Info );
		return true;
	}

}	// CodeGen
