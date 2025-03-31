#pragma once

#include <volk.h>

namespace vkutil {
	void transition_image(VkCommandBuffer cmd, VkImage image, int mipMapLevels, VkImageLayout currentLayout, VkImageLayout newLayout);
	void copy_image_to_image(VkCommandBuffer cmd, VkImage source, VkImage destination, VkExtent2D srcSize, VkExtent2D dstSize);
}