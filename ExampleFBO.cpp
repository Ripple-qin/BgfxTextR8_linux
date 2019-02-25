//
// Created by 王勤龙 on 2018/10/17.
//

#include "ExampleFBO.h"
#include <iostream>

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX

# include <GLFW/glfw3.h>
# include <GLFW/glfw3native.h>

#endif

ExampleFBO::ExampleFBO() {
}

const int width = 3;
const int height = 3;
typedef struct {
    unsigned char readBackData[width * height];
    unsigned char testOOMData[width * height * 3];
} ImageDataObj;

ImageDataObj buffer;
unsigned char *imageReadBackData = buffer.readBackData;

unsigned char mR8_TextureImageData[width * height] = {0};

void ExampleFBO::init(void *window, uint32_t _width, uint32_t _height) {

    bgfx::PlatformData pd;
    pd.ndt = glfwGetX11Display();
    pd.nwh = (void *) (uintptr_t) glfwGetX11Window(((GLFWwindow *) window));
    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;
    bgfx::setPlatformData(pd);

    m_width = _width;
    m_height = _height;
    m_debug = BGFX_DEBUG_NONE;
    m_reset = BGFX_RESET_VSYNC;
    bgfx::Init init;
    init.type = bgfx::RendererType::Enum::Count;
    init.vendorId = 0;
    init.resolution.width = m_width;
    init.resolution.height = m_height;
    init.resolution.reset = m_reset;
    bgfx::init(init);
}

int ExampleFBO::shutdown() {
    bgfx::destroy(m_ori_texture);
    bgfx::destroy(s_textureHandle);
    bgfx::shutdown();
    return 0;
}

bool ExampleFBO::update() {
    memset(mR8_TextureImageData, 254, width * height);
    mR8_TextureImageData[1] = 100;
    mR8_TextureImageData[2] = 101;
    mR8_TextureImageData[3] = 102;
    mR8_TextureImageData[4] = 103;

    for (int i = 0; i < width * height; ++i) {
        std::cout << "Test mR8_TextureImageData[" << i << "]" << "= " << int(mR8_TextureImageData[i]) << std::endl;
    }

    memset(imageReadBackData, 200, width * height);
    memset(buffer.testOOMData, 100, width * height * 3);

    m_ori_texture = loadTextureFromData(mR8_TextureImageData, width, height,
                                        bgfx::TextureFormat::Enum::R8);

    m_blit_texture = bgfx::createTexture2D(width, height, false, 1,
                                           bgfx::TextureFormat::Enum::R8, BGFX_TEXTURE_READ_BACK);
    if (bgfx::isValid(m_blit_texture)) {
        bgfx::blit(1, m_blit_texture, 0, 0, m_ori_texture);
        bgfx::readTexture(m_blit_texture, imageReadBackData);
    }
    bgfx::frame();
    bgfx::frame();

    for (int i = 0; i < width * height; ++i) {
        std::cout << "Test imageReadBackData[" << i << "]" << "= " << int(imageReadBackData[i]) << std::endl;
    }

    for (int i = 0; i < width * height * 3; ++i) {
        std::cout << "Test testOOMData[" << i << "]" << "= " << int(buffer.testOOMData[i]) << std::endl;
    }
    return true;
}

bgfx::TextureHandle ExampleFBO::loadTextureFromData(const unsigned char *imageData, uint32_t width,
                                                    uint32_t height,
                                                    bgfx::TextureFormat::Enum format,
                                                    uint64_t _flags, uint8_t _skip,
                                                    bgfx::TextureInfo *_info,
                                                    bimg::Orientation::Enum *_orientation) {
    bgfx::TextureHandle handle;
    // TODO 需要根据format来计算，临时只区分了BGRA格式和R8
    int multiple = 4;
    if (format == bgfx::TextureFormat::R8) {
        multiple = 1;
    }
    int size = width * height * multiple;
    const bgfx::Memory *mem = bgfx::copy(imageData, size);

    handle = bgfx::createTexture2D(
            uint16_t(width), uint16_t(height), false, 1, format, _flags, mem
    );
    return handle;
}
