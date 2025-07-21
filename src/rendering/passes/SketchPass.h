#pragma once

#include "RenderPass.h"
#include "../assimp/AssimpModelParser.h"

class SketchPass : public RenderPass {
public:
	SketchPass(VkDevice& logicalDevice): RenderPass(logicalDevice)
	{
	}
	SketchPass(const SketchPass& sketchPass)
	: RenderPass(sketchPass.mLogicalDevice),
	  mSketchDescriptorSetLayout(sketchPass.mSketchDescriptorSetLayout)
	{
	}
	~SketchPass() override;
private:
	VkDescriptorSetLayout mSketchDescriptorSetLayout{};
	AssimpModelParser mModelParser;
	void init_descriptors() override;
	void init_pipeline() override;
	void internal_draw(VkCommandBuffer commandBuffer, const std::string& filePath) override;
};