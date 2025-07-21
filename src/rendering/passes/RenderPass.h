#pragma once

#include <stdexcept>
#include <filesystem>
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
	void draw(VkCommandBuffer commandBuffer, const std::string& filePath)
	{
		if (!mInitialized)
		{
			throw std::logic_error("RenderPass must be initialized before recording it on a command buffer");
		}
		if (!std::filesystem::exists(filePath))
		{
			throw std::runtime_error("The file path does not point to an existing file");
		}
		internal_draw(commandBuffer, filePath);
	}
protected:
	VkDevice& mLogicalDevice;
	DescriptorAllocatorGrowable mDescriptorPool;
	bool mInitialized = false;
	virtual void internal_draw(VkCommandBuffer commandBuffer, const std::string& filePath) = 0;
};