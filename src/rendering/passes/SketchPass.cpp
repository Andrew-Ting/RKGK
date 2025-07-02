#include <volk.h>
#include "SketchPass.h"

void SketchPass::init_descriptors()
{
	std::vector<DescriptorAllocatorGrowable::PoolSizeRatio> frame_sizes = {
		{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1 },
		{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1 },
	};

	mDescriptorPool = DescriptorAllocatorGrowable{};
	mDescriptorPool.init(mLogicalDevice, 5, frame_sizes);

	// initialize descriptor layouts
	{
		DescriptorLayoutBuilder builder;
		builder.add_binding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
		builder.add_binding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
		mSketchDescriptorSetLayout = builder.build(mLogicalDevice, VK_SHADER_STAGE_FRAGMENT_BIT);
	}
}
void SketchPass::init_pipeline()
{

}

void SketchPass::internal_draw(VkCommandBuffer commandBuffer)
{

}

SketchPass::~SketchPass()
{
	vkDestroyDescriptorSetLayout(mLogicalDevice, mSketchDescriptorSetLayout, nullptr);
	mDescriptorPool.destroy_pools(mLogicalDevice);
}