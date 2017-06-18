#include "sdlwidget.h"
#include <QElapsedTimer>

#ifdef Q_OS_WIN32
#include "SDL_image.h"
#include "SDL_events.h"
#include "SDL_thread.h"
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#endif

const int FRAME_WIDTH = 1280;
const int FRAME_HEIGHT = 720;


// const int FRAME_WIDTH = 1920;
// const int FRAME_HEIGHT = 1080;

//const int FRAME_WIDTH = 352;
//const int FRAME_HEIGHT = 288;
char szData[FRAME_WIDTH*FRAME_HEIGHT*2] = {0};


//Refresh Event
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)

#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)

int thread_exit=0;
int thread_pause=0;

int sfp_refresh_thread(void *opaque){
    thread_exit=0;
    thread_pause=0;

    while (!thread_exit) {
        if(!thread_pause){
            SDL_Event event;
            event.type = SFM_REFRESH_EVENT;
            SDL_PushEvent(&event);
        }
        SDL_Delay(40);
    }
    thread_exit=0;
    thread_pause=0;
    //Break
    SDL_Event event;
    event.type = SFM_BREAK_EVENT;
    SDL_PushEvent(&event);

    return 0;
}

SDLWidget::SDLWidget()
{

    SDL_Init(SDL_INIT_VIDEO);
    m_pMutex = SDL_CreateMutex();

    m_pRefreshThread = SDL_CreateThread(sfp_refresh_thread,NULL,NULL);
}

SDLWidget::~SDLWidget()
{
    foreach (SDL_Window* pW, m_pMapWindow.values()) {
        SDL_DestroyWindow( pW );
    }

    SDL_Quit();
}

void SDLWidget::addWidget(void *wid)
{
    SDL_LockMutex(m_pMutex);
    if( !m_pMapWindow.contains(wid) ){
        SDL_Window* pWindow = SDL_CreateWindowFrom(wid);
        m_pMapWindow.insert(wid,pWindow);
    }
    SDL_UnlockMutex(m_pMutex);
}

void SDLWidget::resize(void* wid,const QSize &s)
{
    SDL_LockMutex(m_pMutex);
    if( m_pMapWindow.contains(wid) ){
        SDL_Window* pWindow = m_pMapWindow[wid];
        SDL_SetWindowSize( pWindow , s.width(),s.height());
    }
    SDL_UnlockMutex(m_pMutex);
}

void SDLWidget::resize(void *wid, const QRect &r)
{
    SDL_mutexP(m_pMutex);
    if( m_pMapWindow.contains(wid) ){
        SDL_Window* pWindow = m_pMapWindow[wid];
        SDL_SetWindowPosition(pWindow,r.x(),r.y() );
        SDL_SetWindowSize( pWindow , r.width(),r.height());
    }
    SDL_mutexV(m_pMutex);
}

void SDLWidget::run()
{
   // imageRenderRun();
  //  return;

  //  imageSurfaceRun();
  //  return;

    yuvRenderRun();
    return;

}

void SDLWidget::imageSurfaceRun()
{

    SDL_Event event;
    while(1){

        SDL_WaitEvent(&event);
        if( event.type == SFM_REFRESH_EVENT ){

        }else if(event.type==SDL_KEYDOWN){
        //Pause
            if(event.key.keysym.sym==SDLK_SPACE){
                thread_pause=!thread_pause;
            }
        }else if(event.type==SDL_QUIT){
            thread_exit=1;
        }else if(event.type==SFM_BREAK_EVENT){
            break;
        }

        SDL_mutexP(m_pMutex);
        foreach (SDL_Window* pWindow, m_pMapWindow.values()) {

            SDL_Surface* pImageSurface = IMG_Load("/home/suirui/timg.png");
            SDL_Surface* gScreenSurface = SDL_GetWindowSurface(pWindow);

            int x;
            int y;
            int w;
            int h;
            SDL_GetWindowPosition(pWindow,&x,&y);
            SDL_GetWindowSize(pWindow,&w,&h);

            SDL_Rect dstRT;
            dstRT.x = 0;
            dstRT.y = 0;

            dstRT.w = w;
            dstRT.h = h;
            SDL_BlitSurface( pImageSurface ,NULL ,gScreenSurface ,NULL);
            SDL_UpdateWindowSurface(pWindow);//更新显示copy the window surface to the screen
            SDL_FreeSurface(pImageSurface);
        }
        SDL_mutexV(m_pMutex);
    }

	//SDL_LockTexture()
}

void SDLWidget::imageRenderRun()
{

   // SDL_Texture* imageTexture = IMG_LoadTexture( m_pRender ,  "/home/suirui/timg.bmp");

    while(1){

        QElapsedTimer timer;
        timer.start();

        SDL_LockMutex(m_pMutex);

        foreach (SDL_Window* pWindow, m_pMapWindow.values()) {

            m_pRender = SDL_CreateRenderer(pWindow, -1 , SDL_RENDERER_SOFTWARE );
            SDL_Texture* imageTexture = IMG_LoadTexture( m_pRender ,  "/home/suirui/timg.png");

            int x;
            int y;
            int w;
            int h;
            SDL_GetWindowPosition(pWindow,&x,&y);
            SDL_GetWindowSize(pWindow,&w,&h);

            SDL_Rect dstRT;
            dstRT.x = 0;
            dstRT.y = 0;
            dstRT.w = w;
            dstRT.h = h;

            SDL_RenderClear( m_pRender );
            SDL_RenderCopy( m_pRender , imageTexture , NULL , NULL);
            SDL_RenderPresent(m_pRender);

            SDL_DestroyRenderer( m_pRender );
        }
        SDL_UnlockMutex(m_pMutex);

        int remainTime = 16 - timer.elapsed();
        if( remainTime > 0 ){
            msleep(remainTime);
        }
    }

}

void SDLWidget::yuvRenderRun()
{
#ifdef Q_OS_LINUX
    //   FILE * pFile = fopen( "//home//suirui//svn//1_CodeLib//05.PC//SRQT//bin_debug//yuvfile//flower_cif_352_288_420.yuv", "rb" );

       FILE * pFile = fopen( "//home//suirui//svn//1_CodeLib//05.PC//SRQT//bin_debug//yuvfile//1_1920_1080_24fps.yuv", "rb" );

    //   FILE * pFile = fopen( "//home//suirui//svn//1_CodeLib//05.PC//SRQT//bin_debug//yuvfile//flower_cif_352_288_420.yuv", "rb" );
#else
    FILE * pFile = fopen("D:\\1080p\\CrowdRun_1280x720.yuv", "rb");
    //FILE * pFile = fopen("D:\\1_1920_1080_24fps.yuv", "rb");

#endif

    if ( pFile == NULL )
    {
        int u = 0;
    }
    SDL_Rect sdlRT;

    sdlRT.w = FRAME_WIDTH;
    sdlRT.h = FRAME_HEIGHT;
    sdlRT.x = 0;
    sdlRT.y = 0;

    SDL_Rect dstRT;

    dstRT.w = FRAME_WIDTH;
    dstRT.h = FRAME_HEIGHT;
    dstRT.x = 0;
    dstRT.y = 0;
    int iW = FRAME_WIDTH;
    int iH = FRAME_HEIGHT;


    //计算yuv一行数据占的字节数
    int iPitch = iW*SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_IYUV);
    SDL_Event event;

    for(int i=0;i<1000;i++){
        fseek(pFile, 0, SEEK_SET);
        while ( fread( szData, 1, iW*iH*3/2, pFile ) != NULL ){

            SDL_WaitEvent(&event);
            if( event.type == SFM_REFRESH_EVENT ){

            }else if(event.type==SDL_KEYDOWN){
            //Pause
                if(event.key.keysym.sym==SDLK_SPACE){
                    thread_pause=!thread_pause;
                }
            }else if(event.type==SDL_QUIT){
                thread_exit=1;
            }else if(event.type==SFM_BREAK_EVENT){
                break;
            }
            //SDL_mutexP(m_pMutex);
            foreach (SDL_Window* pWindow, m_pMapWindow.values()) {
                int iWidth = 0;
                int iHeight = 0;
                //int x;
                //int y;
                //SDL_GetWindowPosition(pWindow,&x,&y);
                SDL_GetWindowSize( pWindow, &iWidth, &iHeight );

                dstRT.x = 0;
                dstRT.y = 0;
                dstRT.h = iHeight;
                dstRT.w = iWidth;
#ifdef Q_OS_WIN32
                SDL_Renderer * pRender = SDL_CreateRenderer(pWindow, 0, SDL_RENDERER_TARGETTEXTURE);
#else

                SDL_Renderer * pRender = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_SOFTWARE );
#endif               //创建纹理
                SDL_Texture * pTexture = SDL_CreateTexture( pRender,SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, iW, iH );

                int i = SDL_UpdateTexture( pTexture, &sdlRT, szData, iPitch );
                SDL_RenderClear( pRender );
                SDL_RenderCopy( pRender, pTexture, &sdlRT, &dstRT );
                SDL_RenderPresent( pRender );

                if ( pTexture != NULL ){
                    SDL_DestroyTexture( pTexture );
                    pTexture = NULL    ;
                }

                if ( pRender != NULL ){
                    SDL_DestroyRenderer( pRender );
                    pRender = NULL;
                }
            }
           // SDL_mutexV(m_pMutex);
        }
    }

     fclose(pFile);
}
