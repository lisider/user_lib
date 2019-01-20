/*
   This example reads from the default PCM device
   and writes to standard output for 5 seconds of data.
   */
/* Use the newer ALSA API */

#include <stdio.h>
#define ALSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>


void show_params(snd_pcm_hw_params_t *params,snd_pcm_uframes_t frames){
    unsigned int val,val2;
    int dir;

    snd_pcm_hw_params_get_channels(params, &val);
    printf("channels = %d\n", val);
    snd_pcm_hw_params_get_rate(params, &val, &dir);
    printf("rate = %d bps\n", val);
    snd_pcm_hw_params_get_period_time(params,
            &val, &dir);
    printf("period time = %d us\n", val);
    snd_pcm_hw_params_get_period_size(params,
            &frames, &dir);
    printf("period size = %d frames\n", (int)frames);
    snd_pcm_hw_params_get_buffer_time(params,
            &val, &dir);
    printf("buffer time = %d us\n", val);
    snd_pcm_hw_params_get_buffer_size(params,
            (snd_pcm_uframes_t *) &val);
    printf("buffer size = %d frames\n", val);
    snd_pcm_hw_params_get_periods(params, &val, &dir);
    printf("periods per buffer = %d frames\n", val);
    snd_pcm_hw_params_get_rate_numden(params,
            &val, &val2);
    printf("exact rate = %d/%d bps\n", val, val2);
    val = snd_pcm_hw_params_get_sbits(params);
    printf("significant bits = %d\n", val);
    //snd_pcm_hw_params_get_tick_time(params,  &val, &dir);
    printf("tick time = %d us\n", val);
    val = snd_pcm_hw_params_is_batch(params);
    printf("is batch = %d\n", val);
    val = snd_pcm_hw_params_is_block_transfer(params);
    printf("is block transfer = %d\n", val);
    val = snd_pcm_hw_params_is_double(params);
    printf("is double = %d\n", val);
    val = snd_pcm_hw_params_is_half_duplex(params);
    printf("is half duplex = %d\n", val);
    val = snd_pcm_hw_params_is_joint_duplex(params);
    printf("is joint duplex = %d\n", val);
    val = snd_pcm_hw_params_can_overrange(params);
    printf("can overrange = %d\n", val);
    val = snd_pcm_hw_params_can_mmap_sample_resolution(params);
    printf("can mmap = %d\n", val);
    val = snd_pcm_hw_params_can_pause(params);
    printf("can pause = %d\n", val);
    val = snd_pcm_hw_params_can_resume(params);
    printf("can resume = %d\n", val);
    val = snd_pcm_hw_params_can_sync_start(params);
    printf("can sync start = %d\n", val);

}

int main(int argc,char *argv[]){


    long loops;
    int ret,i = 0;
    int size;
    FILE *fp ;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    unsigned int val;
    int dir;
    snd_pcm_uframes_t frames;
    char *buffer = NULL;
    int rate;


    frames = 32;
    rate = 44100;

    fp = fopen("capture.wav","w");
    if(fp < 0){
        printf("open sound.wav fial\n");
        exit(1);
    }

    /* Open PCM device for recording (capture). */
    ret = snd_pcm_open(&handle, "default",
            SND_PCM_STREAM_CAPTURE, 0);
    if (ret < 0) {
        fprintf(stderr,  "unable to open pcm device: %s/n",  snd_strerror(ret));
        exit(1);
    }


    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&params);

    /* Fill it in with default values. */
    snd_pcm_hw_params_any(handle, params);

    /* Set the desired hardware parameters. */
    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params,
            SND_PCM_ACCESS_RW_INTERLEAVED);

    /* Signed 16-bit little-endian format */
    snd_pcm_hw_params_set_format(handle, params,
            SND_PCM_FORMAT_S16_LE);

    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, 2);

    /* 44100 bits/second sampling rate (CD quality) */
    snd_pcm_hw_params_set_rate_near(handle, params,  &rate, &dir);

    /* Set period size to 32 frames. */
    snd_pcm_hw_params_set_period_size_near(handle,  params, &frames, &dir);

    /* Write the parameters to the driver */
    ret = snd_pcm_hw_params(handle, params);
    if (ret < 0) {
        fprintf(stderr,  "unable to set hw parameters: %s/n", snd_strerror(ret));
        exit(1);
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(params,  &frames, &dir);

    size = frames * 4; /* 2 bytes/sample, 2 channels */
    buffer = (char *) malloc(size);
    if(buffer == NULL){
        perror("malloc:");
        exit(3);
    }

    /* We want to loop for 5 seconds */
    snd_pcm_hw_params_get_period_time(params,  &val, &dir);
    loops = 10000000 / val;

    printf("\n\nRecordings starts ...\n");

    while (loops > 0) {
        loops--;
        ret = snd_pcm_readi(handle, buffer, frames);

        i++;

        printf("\r[%d%%]",((int)(i*1.0/(10000000 / val)*100)));

        if (ret == -EPIPE) {
            /* EPIPE means overrun */
            fprintf(stderr, "overrun occurred/n");
            snd_pcm_prepare(handle);
        } else if (ret < 0) {
            fprintf(stderr,
                    "error from read: %s/n",
                    snd_strerror(ret));
        } else if (ret != (int)frames) {
            fprintf(stderr, "short read, read %d frames/n", ret);
        }

        ret = write(1,buffer,size);
        if (ret != size)
            fprintf(stderr,  "short write: wrote %d bytes/n", ret);
    }

    printf("\nRecording completion\n\n");

    /******************打印参数*********************/

    show_params(params,frames);

    /*******************************************************************/
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    fclose(fp);
    free(buffer);
    return 0;
}


