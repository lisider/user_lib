#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alsa/asoundlib.h>

typedef struct WAV_HEADER
{
    char rld[4];    //riff 标志符号
    int rLen;
    char wld[4];    //格式类型（wave）
    char fld[4];    //"fmt"

    int fLen;   //sizeof(wave format matex)

    short wFormatTag;   //编码格式
    short wChannels;    //声道数
    int   nSamplesPersec ;  //采样频率
    int   nAvgBitsPerSample;//WAVE文件采样大小
    short  wBlockAlign; //块对齐
    short wBitsPerSample;   //WAVE文件采样大小

    char dld[4];        //”data“
    int wSampleLength;  //音频数据的大小

} wav_header_t;


void show_wav_info(wav_header_t *wav_header_p){

    //printf("RIFF 标志%s\n",wav_header_p->rld);
    printf("文件大小rLen：%d\n",wav_header_p->rLen);
    //printf("wld=%s\n",wav_header_p->wld);
    //printf("fld=%s\n",wav_header_p->fld);

    // printf("fLen=%d\n",wav_header_p->fLen);

    //printf("wFormatTag=%d\n",wav_header_p->wFormatTag);
    printf("声道数：%d\n",wav_header_p->wChannels);
    printf("采样频率：%d\n",wav_header_p->nSamplesPersec);
    //printf("nAvgBitsPerSample=%d\n",wav_header_p->nAvgBitsPerSample);
    //printf("wBlockAlign=%d\n",wav_header_p->wBlockAlign);
    printf("采样的位数：%d\n",wav_header_p->wBitsPerSample);

    // printf("data=%s\n",wav_header_p->dld);
    printf("wSampleLength=%d\n",wav_header_p->wSampleLength);
}



int set_pcm_play(wav_header_t *wav_header_p,FILE *fp)
{
    int    ret;
    int    size;
    snd_pcm_t*       handle;        //PCI设备句柄
    snd_pcm_hw_params_t*      params;//硬件信息和PCM流配置
    int  dir=0;
    snd_pcm_uframes_t  frames;
    char * buffer = NULL;
    int channels=wav_header_p->wChannels;
    int frequency=wav_header_p->nSamplesPersec;
    int bit=wav_header_p->wBitsPerSample;
    int datablock=wav_header_p->wBlockAlign;



    ret=snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if(ret<0)
    {
        perror("\nopen PCM device failed:");
        exit(1);
    }

    snd_pcm_hw_params_alloca(&params); //分配params结构体

    ret=snd_pcm_hw_params_any(handle, params);//初始化params
    if(ret<0)
    {
        perror("\nsnd_pcm_hw_params_any:");
        exit(1);
    }
    ret=snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);//初始化访问权限
    if(ret<0)
    {
        perror("\nsed_pcm_hw_set_access:");
        exit(1);

    }

    //采样位数
    switch(bit/8)
    {
        case 1:snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_U8);
               break ;
        case 2:snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
               break ;
        case 3:snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S24_LE);
               break ;

    }
    ret=snd_pcm_hw_params_set_channels(handle, params, channels);  //设置声道,1表示单声>道，2表示立体声
    if(ret<0)
    {
        perror("\nsnd_pcm_hw_params_set_channels:");
        exit(1);
    }
    ret=snd_pcm_hw_params_set_rate_near(handle, params, (unsigned int *)&frequency, &dir);  //设置>频率
    if(ret<0)
    {
        perror("\nsnd_pcm_hw_params_set_rate_near:");
        exit(1);
    }

    ret = snd_pcm_hw_params(handle, params);
    if(ret<0)
    {
        perror("\nsnd_pcm_hw_params: ");
        exit(1);
    }

    ret=snd_pcm_hw_params_get_period_size(params, &frames, &dir);  /*获取周期长度*/
    if(ret<0)
    {
        perror("\nsnd_pcm_hw_params_get_period_size:");
        exit(1);
    }


    fseek(fp,58,SEEK_SET);  //定位歌曲到数据区

    size = frames * datablock;   /*4 代表数据快长度*/
    buffer = (char *)malloc(size);
    if(buffer == NULL){
        perror("malloc:");
        exit(2);
    }

    while (1)
    {
        memset(buffer,0,sizeof(buffer));
        ret = fread(buffer, 1, size, fp);
        if(ret == 0)
        {
            //sleep(2);
            //printf("播放结束\n");
            break;
        }
        // 写音频数据到PCM设备
        while(ret = snd_pcm_writei(handle, buffer, frames)<0)
        {
            usleep(2000);
            if (ret == -EPIPE)
            {
                /* EPIPE means underrun */
                fprintf(stderr, "underrun occurred\n");
                //完成硬件参数设置，使设备准备好
                snd_pcm_prepare(handle);
            }
            else if (ret < 0)
            {
                fprintf(stderr,
                        "error from writei: %s\n",
                        snd_strerror(ret));
            }
        }

    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
    printf("播放结束\n");
    return 0;
}


int main(int argc,char *argv[])
{

    if(argc != 2){
        printf("Usage:\n%s to_play.wav\n",argv[0]);
        exit(1);
    }

    int nread;
    FILE *fp;
    wav_header_t wav_header;

    fp = fopen(argv[1],"rb");
    if(fp == NULL){
        perror("open file failed:\n");
        exit(1);
    }

    nread = fread(&wav_header,1,sizeof(wav_header),fp);
    if(nread != sizeof(wav_header_t)){
        perror("read file failed:\n");
        exit(2);
    }

    show_wav_info(&wav_header);

    set_pcm_play(&wav_header,fp);
    return 0;
}

