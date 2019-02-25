//
// Created by 王勤龙 on 2018/10/17.
//

#ifndef NATIVE_ACTIVITY_EXAMPLECUBES_H
#define NATIVE_ACTIVITY_EXAMPLECUBES_H


#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "bgfx/platform.h"

class ExampleFBO{


public:
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_debug;
    uint32_t m_reset;

    bgfx::TextureHandle m_ori_texture;
    bgfx::TextureHandle m_blit_texture;
    bgfx::UniformHandle s_textureHandle;

    bgfx::FrameBufferHandle m_fbh = BGFX_INVALID_HANDLE;

public:
    ExampleFBO();

    ///
    void init(void * window, uint32_t _width, uint32_t _height);

    ///
    int shutdown();

    ///
    bool update();

    bgfx::TextureHandle loadTextureFromData(const unsigned char *imageData, uint32_t width,
                                            uint32_t height,
                                            bgfx::TextureFormat::Enum format,
                                            uint64_t _flags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_TEXTURE_RT, uint8_t _skip = 0,
                                            bgfx::TextureInfo *_info = NULL,
                                            bimg::Orientation::Enum *_orientation = NULL);
};


#endif //NATIVE_ACTIVITY_EXAMPLECUBES_H
