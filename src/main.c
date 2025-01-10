#define SI_IMPLEMENTATION 1
#define RGFW_IMPLEMENTATION
#define RGFWDEF
//#define RGFW_ALLOC_DROPFILES
//#define RGFW_PRINT_ERRORS
//#define RGFW_DEBUG

#include <sili.h>
#include <RGFW.h>

void drawLoop(RGFW_window* w); /* I seperate the draw loop only because it's run twice */


SI_THREAD_PROC(loop2);

siColor icon[3 * 3] = {
    SI_RGB(255, 0, 0), SI_RGB(0, 255, 0), SI_RGB(255, 0, 0),
    SI_RGB(0, 0, 255), SI_RGB(255, 255, 0), SI_RGB(0, 0, 255),
    SI_RGB(255, 0, 0), SI_RGB(0, 255, 0), SI_RGB(255, 0, 0)
};
b32 mainWindowIsRunning = true,
	subWindowIsRunning = true;
RGFW_mouse* mouse;

/* callbacks are another way you can handle events in RGFW */
void refreshCallback(RGFW_window* win) {
    drawLoop(win);
}


RGFW_window* win2;

int main(void) {
	RGFW_setClassName(SI_STR("RGFW Basic"));

	RGFW_window* win = RGFW_createWindow(
		SI_STR("RGFW Example Window"), RGFW_RECT(500, 500, 500, 500),
		RGFW_windowAllowDND | RGFW_windowCenter
	);
	SI_ASSERT_NOT_NIL(win);

    RGFW_window_setIcon(win, (u8*)icon, RGFW_AREA(3, 3), 4);

    RGFW_setWindowRefreshCallback(refreshCallback);

    #if SI_SYSTEM_IS_APPLE
	/* You can also allocate your own window. */
	win2 = si_mallocItem(RGFW_window);
    siError err = RGFW_createWindowPtr(
		SI_STR("subwindow"), RGFW_RECT(200, 200, 200, 200), 0, win2
	);
	SI_ASSERT(err.code == 0);
	#else
	siThread subWindowThread;
	si_threadMakeAndRun(loop2, nil, &subWindowThread);
	#endif


    glEnable(GL_BLEND);
    glClearColor(0, 0, 0, 0);

    RGFW_window_setMouseStandard(win, RGFW_mouseResizeNESW);

    u32 fps = 0;

    while (subWindowIsRunning && !RGFW_isPressed(win, RGFW_keyEscape)) {
        #ifdef SI_SYSTEM_IS_APPLE
        if (win2) RGFW_window_checkEvent(win2);
        #endif

        RGFW_window_eventWait(win, RGFW_waitNext);

        while (RGFW_window_checkEvent(win) != NULL) {
            if (win->event.type == RGFW_windowMoved) {
                si_printf("window moved\n");
            }
            else if (win->event.type == RGFW_windowResized) {
                si_printf("window resized\n");
            }
            if (win->event.type == RGFW_quit) {
				subWindowIsRunning = false;
                break;
            }
            if (RGFW_isPressed(win, RGFW_keyUp)) {
                char* str = RGFW_readClipboard(NULL);
                si_printf("Pasted : %s\n", str);
                free(str);
            }
            else if (RGFW_isPressed(win, RGFW_keyDown))
                RGFW_writeClipboard("DOWN", 4);
            else if (RGFW_isPressed(win, RGFW_keySpace))
                si_printf("fps : %i\n", fps);
            else if (RGFW_isPressed(win, RGFW_keyW))
                RGFW_window_setMouseDefault(win);
            else if (RGFW_isPressed(win, RGFW_keyQ))
                RGFW_window_showMouse(win, 0);
            else if (RGFW_isPressed(win, RGFW_keyT)) {
				if (mouse == nil) {
					mouse = RGFW_loadMouse((u8*)icon, RGFW_AREA(3, 3), 4);
				}

                RGFW_window_setMouse(win, icon);
            }

            if (win->event.type == RGFW_dnd) {
				for_range (i, 0, win->event.droppedFilesCount) {
                    si_printf("dropped : %s\n", win->event.droppedFiles[i]);
				}
            }

            else if (win->event.type == RGFW_gamepadButtonPressed)
                si_printf("pressed %i\n", win->event.button);

            else if (win->event.type == RGFW_gamepadAxisMove)
                si_printf("Gamepad (%i) axis (%i) {%i, %i}\n", win->event.gamepad, win->event.whichAxis, win->event.axis[win->event.whichAxis].x, win->event.axis[win->event.whichAxis].y);
        }

        drawLoop(win);
        fps = RGFW_window_checkFPS(win, 0);
    }

	mainWindowIsRunning = false;
	RGFW_window_close(win);

	if (mouse) {
		RGFW_freeMouse(mouse);
	}
}

void drawLoop(RGFW_window *w) {
    RGFW_window_makeCurrent(w);

    #ifdef RGFW_OPENGL
    glClearColor(255, 255, 255, 255);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); glVertex2f(-0.6f, -0.75f);
        glColor3f(0, 1, 0); glVertex2f( 0.6f, -0.75f);
        glColor3f(0, 0, 1); glVertex2f( 0.0f,  0.75f);
    glEnd();
    #endif

    RGFW_window_swapBuffers(w);
}

rawptr loop2(rawptr data) {
    #if !SI_SYSTEM_IS_APPLE
	/* You can also allocate your own window. */
	win2 = si_mallocItem(RGFW_window);
    siError err = RGFW_createWindowPtr(
		SI_STR("subwindow"), RGFW_RECT(200, 200, 200, 200), 0, win2
	);
	SI_ASSERT(err.code == 0);
    #endif

	RGFW_window* win = win2;
    while (mainWindowIsRunning) {
		/*
            not using a while loop here because there is only one event I care about
        */
        #if !SI_SYSTEM_IS_APPLE
        RGFW_window_checkEvent(win);
        #endif

        /*
            I could've also done

            if (RGFW_checkEvents(win).type == RGFW_quit)
        */

        if (win->event.type == RGFW_quit)
            break;

        if (win->event.type == RGFW_mouseButtonPressed) {
			#if !SI_SYSTEM_IS_APPLE
            RGFW_stopCheckEvents();
            #endif
        }

        if (win->event.type == RGFW_gamepadButtonPressed)
            si_printf("pressed %i\n", win->event.button);

        else if (win->event.type == RGFW_gamepadAxisMove && !win->event.button)
            si_printf("Gamepad (%i) axis (%i) {%i, %i}\n", win->event.gamepad, win->event.whichAxis, win->event.axis[win->event.whichAxis].x, win->event.axis[win->event.whichAxis].y);
        drawLoop(win);
    }

	subWindowIsRunning = false;
    RGFW_window_close(win);
	si_mfree(win);

	#if SI_SYSTEM_IS_APPLE
	win2 = nil;
	#endif

	return nil;
	SI_UNUSED(data);
}
