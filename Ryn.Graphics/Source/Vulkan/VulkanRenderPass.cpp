#include "VulkanRenderPass.hpp"

namespace Ryn
{
    void VulkanRenderPass::CreateRenderPass(const VulkanSwapchain& swapchain)
    {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapchain.GetVkSurfaceFormat().format;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        createInfo.attachmentCount = 1;
        createInfo.pAttachments = &colorAttachment;
        createInfo.subpassCount = 1;
        createInfo.pSubpasses = &subpass;
        createInfo.dependencyCount = 1;
        createInfo.pDependencies = &dependency;

        VkResult result = vkCreateRenderPass(_device->GetVkDevice(), &createInfo, {}, &_renderPass);
        VulkanCheck(result, "Failed to create render pass");
    }

    void VulkanRenderPass::DestroyRenderPass()
    {
        if (_renderPass)
        {
            vkDestroyRenderPass(_device->GetVkDevice(), _renderPass, {});
            _renderPass = {};
        }
    }

    void VulkanRenderPass::CreateFramebuffers(const VulkanSwapchain& swapchain)
    {
        _framebuffers.Reserve(swapchain.GetImageCount());

        VkExtent2D extent = swapchain.GetVkExtent();
        for (VkImageView swapchainImageView : swapchain.GetSwapchainImageViews())
        {
            VkImageView attachments[] = {swapchainImageView};

            VkFramebufferCreateInfo framebufferCreateInfo{};
            framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferCreateInfo.renderPass = _renderPass;
            framebufferCreateInfo.attachmentCount = 1;
            framebufferCreateInfo.pAttachments = attachments;
            framebufferCreateInfo.width = extent.width;
            framebufferCreateInfo.height = extent.height;
            framebufferCreateInfo.layers = 1;

            VkFramebuffer framebuffer;
            VkResult result = vkCreateFramebuffer(_device->GetVkDevice(), &framebufferCreateInfo, {}, &framebuffer);
            VulkanCheck(result, "Failed to create framebuffer");
        }
    }

    void VulkanRenderPass::DestroyFramebuffers()
    {
        for (VkFramebuffer framebuffer : _framebuffers)
        {
            vkDestroyFramebuffer(_device->GetVkDevice(), framebuffer, {});
        }

        _framebuffers.Clear();
    }
}
