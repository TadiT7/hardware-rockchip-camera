/*
 * Copyright (C) Texas Instruments - http://www.ti.com/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef ANDROID_HARDWARE_CAMERA_HARDWARE_H
#define ANDROID_HARDWARE_CAMERA_HARDWARE_H
 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <utils/Log.h>
#include <utils/threads.h>
#include <cutils/properties.h>
#include <cutils/atomic.h>
#include <linux/version.h>
#include <linux/videodev2.h>
#include <binder/MemoryBase.h>
#include <binder/MemoryHeapBase.h>
#include <utils/threads.h>
#include <ui/GraphicBufferAllocator.h>
#include <ui/GraphicBufferMapper.h>
#include <ui/GraphicBuffer.h>
#include <system/window.h>
#include <camera/Camera.h>
#include <hardware/camera.h>
#include <camera/CameraParameters.h>


#include "MessageQueue.h"
#include "../jpeghw/release/encode_release/hw_jpegenc.h"
#include "../libgralloc/gralloc_priv.h"


namespace android {

/*
*v0.1.0 : CameraHal support for android 4.0(ICS);
*v0.1.1 : CameraHal support query framerate from driver, display thread support NativeWindow sync and asyc mode;
*/
#define CONFIG_CAMERAHAL_VERSION KERNEL_VERSION(0, 1, 1)

/*  */
#define CONFIG_CAMERA_PRVIEW_BUF_CNT    4           

#define CAMERA_PMEM_NAME                "/dev/pmem_cam"
#define CAMERA_DRIVER_SUPPORT_FORMAT_MAX   32

#define RAW_BUFFER_SIZE_5M          0x800000
#define RAW_BUFFER_SIZE_3M          0x500000
#define RAW_BUFFER_SIZE_2M          0x300000
#define RAW_BUFFER_SIZE_1M          0x200000
#define RAW_BUFFER_SIZE_0M3          0x100000

#define JPEG_BUFFER_SIZE_5M          0x400000
#define JPEG_BUFFER_SIZE_3M          0x300000
#define JPEG_BUFFER_SIZE_2M          0x300000
#define JPEG_BUFFER_SIZE_1M          0x200000
#define JPEG_BUFFER_SIZE_0M3          0x100000

#define V4L2_BUFFER_MAX             32
#define V4L2_BUFFER_MMAP_MAX        16
#define PAGE_ALIGN(x)   (((x) + 0xFFF) & (~0xFFF)) // Set as multiple of 4K




#define CAMHAL_GRALLOC_USAGE GRALLOC_USAGE_HW_TEXTURE | \
                             GRALLOC_USAGE_HW_RENDER | \
                             GRALLOC_USAGE_SW_READ_RARELY | \
                             GRALLOC_USAGE_SW_WRITE_NEVER

struct CamCaptureInfo_s
{
	int input_phy_addr;
	int output_phy_addr;
	int output_vir_addr;
	int output_buflen;
};

struct CamMemHeapInfo_s
{
	sp<MemoryHeapBase> heap;
    sp<IMemory> buffer; 
};

typedef struct rk_previewbuf_info {
    Mutex lock;
    buffer_handle_t* buffer_hnd;
    private_handle_t* priv_hnd;
    camera_memory_t* video_buf;
    int phy_addr;
    int buf_state;
} rk_previewbuf_info_t;

class CameraHal {
public:  
/*--------------------Interface Methods---------------------------------*/
    /** Set the ANativeWindow to which preview frames are sent */
    int setPreviewWindow(struct preview_stream_ops *window);

    /** Set the notification and data callbacks */
    void setCallbacks(camera_notify_callback notify_cb,
            camera_data_callback data_cb,
            camera_data_timestamp_callback data_cb_timestamp,
            camera_request_memory get_memory,
            void *user);

    /**
     * The following three functions all take a msg_type, which is a bitmask of
     * the messages defined in include/ui/Camera.h
     */

    /**
     * Enable a message, or set of messages.
     */
    void enableMsgType(int32_t msg_type);

    /**
     * Disable a message, or a set of messages.
     *
     * Once received a call to disableMsgType(CAMERA_MSG_VIDEO_FRAME), camera
     * HAL should not rely on its client to call releaseRecordingFrame() to
     * release video recording frames sent out by the cameral HAL before and
     * after the disableMsgType(CAMERA_MSG_VIDEO_FRAME) call. Camera HAL
     * clients must not modify/access any video recording frame after calling
     * disableMsgType(CAMERA_MSG_VIDEO_FRAME).
     */
    void disableMsgType(int32_t msg_type);

    /**
     * Query whether a message, or a set of messages, is enabled.  Note that
     * this is operates as an AND, if any of the messages queried are off, this
     * will return false.
     */
    int msgTypeEnabled(int32_t msg_type);

    /**
     * Start preview mode.
     */
    int startPreview();

    /**
     * Stop a previously started preview.
     */
    void stopPreview();

    /**
     * Returns true if preview is enabled.
     */
    int previewEnabled();

    /**
     * Request the camera HAL to store meta data or real YUV data in the video
     * buffers sent out via CAMERA_MSG_VIDEO_FRAME for a recording session. If
     * it is not called, the default camera HAL behavior is to store real YUV
     * data in the video buffers.
     *
     * This method should be called before startRecording() in order to be
     * effective.
     *
     * If meta data is stored in the video buffers, it is up to the receiver of
     * the video buffers to interpret the contents and to find the actual frame
     * data with the help of the meta data in the buffer. How this is done is
     * outside of the scope of this method.
     *
     * Some camera HALs may not support storing meta data in the video buffers,
     * but all camera HALs should support storing real YUV data in the video
     * buffers. If the camera HAL does not support storing the meta data in the
     * video buffers when it is requested to do do, INVALID_OPERATION must be
     * returned. It is very useful for the camera HAL to pass meta data rather
     * than the actual frame data directly to the video encoder, since the
     * amount of the uncompressed frame data can be very large if video size is
     * large.
     *
     * @param enable if true to instruct the camera HAL to store
     *        meta data in the video buffers; false to instruct
     *        the camera HAL to store real YUV data in the video
     *        buffers.
     *
     * @return OK on success.
     */
    int storeMetaDataInBuffers(int enable);

    /**
     * Start record mode. When a record image is available, a
     * CAMERA_MSG_VIDEO_FRAME message is sent with the corresponding
     * frame. Every record frame must be released by a camera HAL client via
     * releaseRecordingFrame() before the client calls
     * disableMsgType(CAMERA_MSG_VIDEO_FRAME). After the client calls
     * disableMsgType(CAMERA_MSG_VIDEO_FRAME), it is the camera HAL's
     * responsibility to manage the life-cycle of the video recording frames,
     * and the client must not modify/access any video recording frames.
     */
    int startRecording();

    /**
     * Stop a previously started recording.
     */
    void stopRecording();

    /**
     * Returns true if recording is enabled.
     */
    int recordingEnabled();

    /**
     * Release a record frame previously returned by CAMERA_MSG_VIDEO_FRAME.
     *
     * It is camera HAL client's responsibility to release video recording
     * frames sent out by the camera HAL before the camera HAL receives a call
     * to disableMsgType(CAMERA_MSG_VIDEO_FRAME). After it receives the call to
     * disableMsgType(CAMERA_MSG_VIDEO_FRAME), it is the camera HAL's
     * responsibility to manage the life-cycle of the video recording frames.
     */
    void releaseRecordingFrame(const void *opaque);

    /**
     * Start auto focus, the notification callback routine is called with
     * CAMERA_MSG_FOCUS once when focusing is complete. autoFocus() will be
     * called again if another auto focus is needed.
     */
    int autoFocus();

    /**
     * Cancels auto-focus function. If the auto-focus is still in progress,
     * this function will cancel it. Whether the auto-focus is in progress or
     * not, this function will return the focus position to the default.  If
     * the camera does not support auto-focus, this is a no-op.
     */
    int cancelAutoFocus();

    /**
     * Take a picture.
     */
    int takePicture();

    /**
     * Cancel a picture that was started with takePicture. Calling this method
     * when no picture is being taken is a no-op.
     */
    int cancelPicture();

    /**
     * Set the camera parameters. This returns BAD_VALUE if any parameter is
     * invalid or not supported.
     */
    int setParameters(const char *parms);
    int setParameters(const CameraParameters &params_set);

    /** Retrieve the camera parameters.  The buffer returned by the camera HAL
        must be returned back to it with put_parameters, if put_parameters
        is not NULL.
     */
    char* getParameters();

    /** The camera HAL uses its own memory to pass us the parameters when we
        call get_parameters.  Use this function to return the memory back to
        the camera HAL, if put_parameters is not NULL.  If put_parameters
        is NULL, then you have to use free() to release the memory.
    */
    void putParameters(char *);

    /**
     * Send command to camera driver.
     */
    int sendCommand(int32_t cmd, int32_t arg1, int32_t arg2);

    /**
     * Release the hardware resources owned by this object.  Note that this is
     * *not* done in the destructor.
     */
    void release();

    /**
     * Dump state of the camera hardware
     */
    int dump(int fd);

/*--------------------Internal Member functions - Public---------------------------------*/
    /** Constructor of CameraHal */
    CameraHal(int cameraId);

    // Destructor of CameraHal
    ~CameraHal();    

    int getCameraFd();
    
private:

    class PreviewThread : public Thread {
        CameraHal* mHardware;
    public:
        PreviewThread(CameraHal* hw)
            : Thread(false), mHardware(hw) { }

        virtual bool threadLoop() {
            mHardware->previewThread();

            return false;
        }
    };

    class DisplayThread : public Thread {
        CameraHal* mHardware;        
    public:
        DisplayThread(CameraHal* hw)
            : Thread(false), mHardware(hw){}

        virtual bool threadLoop() {
            mHardware->displayThread();

            return false;
        }
    };

    class PictureThread : public Thread {
        CameraHal* mHardware;
    public:
        PictureThread(CameraHal* hw)
            : Thread(false), mHardware(hw) { }

        virtual bool threadLoop() {
            mHardware->pictureThread();

            return false;
        }
    };

    class AutoFocusThread : public Thread {
        CameraHal* mHardware;
    public:
        AutoFocusThread(CameraHal* hw)
            : Thread(false), mHardware(hw) { }

        virtual bool threadLoop() {
            mHardware->autofocusThread();

            return false;
        }
    };

	class CommandThread : public Thread {
        CameraHal* mHardware;
    public:
        CommandThread(CameraHal* hw)
            : Thread(false), mHardware(hw) { }

        virtual bool threadLoop() {
            mHardware->commandThread();

            return false;
        }
    };

    void displayThread();
    void previewThread();
	void commandThread();
    void pictureThread();
    void autofocusThread();
    void initDefaultParameters();
    int capturePicture(struct CamCaptureInfo_s *capture);
	int capturePicturePmemInfoSet(int pmem_fd, int input_offset, int out_offset);
    int cameraCreate(int cameraId);
    int cameraDestroy();
    int cameraConfig(const CameraParameters &params);
    int cameraQuery(CameraParameters &params);
    int cameraSetSize(int w, int h,  int fmt);
    int cameraStart();
    int cameraStop();
	int cameraAutoFocus(const char *focus);
    int Jpegfillgpsinfo(RkGPSInfo *gpsInfo);
    int Jpegfillexifinfo(RkExifInfo *exifInfo);

    int cameraHeapBufferCreate(int rawBufferSize, int jpegBufferSize);
    int cameraHeapBufferDestory();
    int cameraPmemBufferFlush(sp<MemoryHeapBase> heap, sp<IMemory> buf);
    int cameraFormatConvert(int v4l2_fmt_src, int v4l2_fmt_dst, const char *android_fmt_dst, char *srcbuf, char *dstbuf, int w, int h);
    int cameraPreviewBufferCreate(int width, int height, unsigned int fmt,unsigned int numBufs);
    int cameraPreviewBufferDestory();
    int cameraPreviewBufferSetSta(rk_previewbuf_info_t *buf_hnd,int cmd, int set);
    int cameraFramerateQuery(unsigned int format, unsigned int w, unsigned int h, int *min, int *max);
    int cameraFpsInfoSet(CameraParameters &params);

    int cameraDisplayThreadStart(int done);
    int cameraDisplayThreadPause(int done);
    int cameraDisplayThreadStop(int done);
    
    char *cameraDevicePathCur;    
    char cameraCallProcess[30];
    struct v4l2_capability mCamDriverCapability;
    unsigned int mCamDriverFrmWidthMax;
    unsigned int mCamDriverFrmHeightMax;
    unsigned int mCamDriverPreviewFmt;
    unsigned int mCamDriverPictureFmt;
    unsigned int mCamDriverSupportFmt[CAMERA_DRIVER_SUPPORT_FORMAT_MAX];
    enum v4l2_memory mCamDriverV4l2MemType;
    char *mCamDriverV4l2Buffer[V4L2_BUFFER_MAX];
    unsigned int mCamDriverV4l2BufferLen;

    mutable Mutex mLock;        // API lock -- all public methods
    CameraParameters mParameters;
    Mutex mANativeWindowLock;
    Condition mANativeWindowCond;
    preview_stream_ops_t *mANativeWindow;
    int mMsgEnabled;
    int mPreviewErrorFrameCount;
	int mPreviewBufferCount;
    int mPreviewWidth;
    int mPreviewHeight;
    int mJpegBufferSize;
    int mRawBufferSize;
    int mPreviewFrameSize;    
    int mPmemHeapPhyBase;
    volatile int32_t mPreviewStartTimes;
    
    rk_previewbuf_info_t mPreviewBufferMap[CONFIG_CAMERA_PRVIEW_BUF_CNT];

    camera_memory_t* mPreviewMemory;
    unsigned char* mPreviewBufs[CONFIG_CAMERA_PRVIEW_BUF_CNT];
    camera_memory_t* mVideoBufs[CONFIG_CAMERA_PRVIEW_BUF_CNT];
    
    sp<MemoryHeapBase> mMemHeap;
	sp<MemoryHeapBase> mMemHeapPmem;
    sp<IMemory> mJpegBuffer; 
    sp<IMemory> mRawBuffer;  
    unsigned int CameraHal_SupportFmt[5];
    
    sp<DisplayThread>  mDisplayThread;
    sp<PreviewThread>  mPreviewThread;
	sp<CommandThread>  mCommandThread;
    sp<PictureThread>  mPictureThread;
    sp<AutoFocusThread>  mAutoFocusThread;
    int mPreviewRunning;
    Mutex mPreviewLock;
    Condition mPreviewCond;
    bool mPreviewCmdReceived;
    int mDisplayRuning;
    Mutex mDisplayLock;
    Condition mDisplayCond;    
    bool mRecordRunning; 
    Mutex mPictureLock;
    int mPictureRunning;
    Mutex mAutoFocusLock;
    Condition mAutoFocusCond;
    bool mExitAutoFocusThread; 
    
    int iCamFd;
    int iPmemFd;
    int mPmemSize; 
    int mCamId;
    
    bool mDriverMirrorSupport;
    bool mDriverFlipSupport;
    
    struct v4l2_querymenu mWhiteBalance_menu[20];
    int mWhiteBalance_number;

    struct v4l2_querymenu mEffect_menu[20];
    int mEffect_number;

    struct v4l2_querymenu mScene_menu[20];
    int mScene_number;
    
    int mZoomMin;
    int mZoomMax;
    int mZoomStep;

    struct v4l2_querymenu mFlashMode_menu[20];
    int mFlashMode_number;

    double mGps_latitude;
    double mGps_longitude;
    double mGps_altitude;
    long mGps_timestamp;

    enum PreviewBufStatus {
        CMD_PREVIEWBUF_DISPING,
        CMD_PREVIEWBUF_ENCING,
        CMD_PREVIEWBUF_WRITING,
    };

    enum DisplayRunStatus {
        STA_DISPLAY_PAUSE,
        STA_DISPLAY_RUN,
        STA_DISPLAY_STOP
    };

    enum PreviewRunStatus {
        STA_PREVIEW_PAUSE,
        STA_PREVIEW_RUN,
        STA_PREVIEW_STOP,
    };

    enum PictureRunStatus {
        STA_PICTURE_STOP,
        STA_PICTURE_RUN,
        STA_PICTURE_WAIT_STOP,
    };
    enum DisplayThreadCommands {
		// Comands
		CMD_DISPLAY_PAUSE,        
        CMD_DISPLAY_START,
        CMD_DISPLAY_STOP,
        CMD_DISPLAY_INVAL
    };
    enum PreviewThreadCommands {
		// Comands
        CMD_PREVIEW_STAREQ,
        CMD_PREVIEW_INVAL
    };
    enum CommandThreadCommands { 
		// Comands
        CMD_PREVIEW_START,
        CMD_PREVIEW_STOP,
        CMD_PREVIEW_CAPTURE,
        CMD_PREVIEW_CAPTURE_CANCEL,
        CMD_PREVIEW_QBUF,        
        
        CMD_AF_START,
        CMD_AF_CANCEL,
        
        CMD_EXIT,
        
        // ACKs
        CMD_ACK,
        CMD_NACK,
    };
    MessageQueue    displayThreadCommandQ;
    MessageQueue    displayThreadAckQ;
    MessageQueue    previewThreadCommandQ;
    MessageQueue    previewThreadAckQ;
    MessageQueue    commandThreadCommandQ;
    MessageQueue    commandThreadAckQ;

    camera_notify_callback mNotifyCb;
    camera_data_callback mDataCb;    
    camera_data_timestamp_callback mDataCbTimestamp;
    camera_request_memory mRequestMemory;
    void  *mCallbackCookie;
};

}; // namespace android
#endif
