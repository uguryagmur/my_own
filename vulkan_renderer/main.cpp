#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <bits/stdc++.h>


class BasicTriangleApplication
{
	public:
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;

		void run()
		{
			initWindow();
			initVulkan();
			mainLoop();
			cleanup();
		}
	
	private:
		void initWindow()
		{
			glfwInit();

			// window configs
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Renderer", nullptr, nullptr);
			if (!window)
				throw std::runtime_error("window creation is failed");
		}

		void initVulkan()
		{
			createInstance();
		}

		void mainLoop()
		{
			while (!glfwWindowShouldClose(window))
			{
				glfwPollEvents();
			}
		}

		void cleanup()
		{
			vkDestroyInstance(instance, nullptr);

			glfwDestroyWindow(window);
			glfwTerminate();
		}

		void createInstance()
		{
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Basic Triangle";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;

			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;
			createInfo.enabledLayerCount = 0;

			if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
				throw std::runtime_error("failed to create instance");

			uint32_t extensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
			std::vector<VkExtensionProperties> extensions(extensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
			std::cerr << "available extensions:\n";
			for (const auto& extension: extensions)
				std::cerr << "\tExtension Name -> " << extension.extensionName << '\n';
		}

		GLFWwindow* window;
		VkInstance instance;
};


int main()
{
	BasicTriangleApplication app;

	try { app.run(); }
	catch (const std::exception& e)
	{
		std::cerr << "An error occured:\n";
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
