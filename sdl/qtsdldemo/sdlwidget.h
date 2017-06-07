﻿#ifndef SDLWIDGET_H
#define SDLWIDGET_H

#include <QThread>
#include <QSize>

#include <QMap>
#include <QRect>

struct SDL_Window;
struct SDL_mutex;
struct SDL_Renderer;
class SDLWidget : public QThread
{
public:
    SDLWidget();
    ~SDLWidget();

    void addWidget(void* wid);
    void resize(void*wid,const QSize &s);
    void resize(void*wid,const QRect &r);
protected:
    void run();

    void imageSurfaceRun();
    void imageRenderRun();
    void yuvRenderRun();
private:
    QMap<void* , SDL_Window*> m_pMapWindow;
    QList<SDL_Window*> m_pWindowList;
    SDL_Window* m_pWindow;
    SDL_mutex* m_pMutex;
    SDL_Renderer* m_pRender;
};

#endif // SDLWIDGET_H
