#pragma once

#include <stdexcept>
#include "../vk_descriptors.h"
class RenderPass {

public:
	RenderPass(VkDevice& logicalDevice): mLogicalDevice(logicalDevice), mDescriptorPool()
	{
	}
	RenderPass(RenderPass&) = default;
	virtual ~RenderPass() = default;

	void init()
	{
		if (mInitialized)
		{
			throw std::logic_error("RenderPass already initialized");
		}
		init_descriptors();
		init_pipeline();
	}
	virtual void init_descriptors() = 0;
	virtual void init_pipeline() = 0;
	void draw(VkCommandBuffer commandBuffer)
	{
		if (!mInitialized)
		{
			throw std::logic_error("RenderPass must be initialized before recording it on a command buffer");
		}
		internal_draw(commandBuffer);
	}
protected:
	VkDevice& mLogicalDevice;
	DescriptorAllocatorGrowable mDescriptorPool;
	bool mInitialized = false;
	virtual void internal_draw(VkCommandBuffer commandBuffer) = 0;
};