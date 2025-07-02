#pragma once

#include <volk.h>
#include <map>
#include <memory>
#include <string>
#include "deletion_queue.h"
#include "vk_descriptors.h"
#include "passes/RenderPass.h"

struct FrameData {
	VkCommandPool mCommandPool;
	VkCommandBuffer mMainCommandBuffer;
	VkSemaphore mSwapchainSemaphore, mRenderSemaphore;
	VkFence mRenderFence;
	DeletionQueue mDeletionQueue;
	DescriptorAllocatorGrowable mFrameDescriptors;
	std::map<std::string, std::unique_ptr<RenderPass>> mRenderPasses;
};