#ifndef KI_FOUNDATION_PCH_H
#define KI_FOUNDATION_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  //__declspec(dllexport)
#endif

#pragma warning( disable : 4251 )
#define USE_VAR(x) (void)x;

#include<memory>
#include<string>
#include <iostream>
#include <vector>
#include<iostream>
#include<fstream>
#include <stack>
#include <assert.h>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

#include "Interface.h"
#include "IController.h"
#include "ICommand.h"
#include "CommandManager.h"
#include "IEventArgs.h"
#include "IObserver.h"

#include "SystemTypes.h"
#include "Logger.h"
#include "Mouse.h"
#include "MouseInput.h"
#include "WindowEvent.h"

#endif //KI_FOUNDATION_PCH_H
