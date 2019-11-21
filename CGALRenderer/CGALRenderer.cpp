namespace KI
{
void ScrollCallBack(GLFWwindow* window, double x, double y)
{
	MouseInput input;
	input.SetWheel(y);
	input.SetEvent(MOUSE_EVENT::MOUSE_EVENT_WHEEL);
	TheApp()->ProcessMouseEvent(input);
}

void CursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	MouseInput input;
	input.SetPosition(xpos, ypos);

	input.SetEvent(MOUSE_EVENT::MOUSE_EVENT_MOVE);

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		input.SetPress(MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}
	else
	{
		input.SetRelease(MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		input.SetPress(MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}
	else
	{
		input.SetRelease(MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		input.SetPress(MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}
	else
	{
		input.SetRelease(MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}

	TheApp()->ProcessMouseEvent(input);
}

void WindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowEvent winEvent;
	winEvent.SetEvent(WINDOW_EVENT::WINDOW_EVENT_RESIZE);
	winEvent.SetSize(width, height);
	TheApp()->ProcessWindowEvent(winEvent);
}

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	MOUSE_BUTTON mouseButton;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseButton = MOUSE_BUTTON_LEFT;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseButton = MOUSE_BUTTON_MIDDLE;
		break; 
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseButton = MOUSE_BUTTON_RIGHT;
		break;
	default:
		break;
	}

	double posX;
	double posY;
	glfwGetCursorPos(window, &posX, &posY);

	MouseInput input;
	input.SetPosition(posX, posY);
	if (action == GLFW_PRESS)
	{
		input.SetEvent(MOUSE_EVENT_DOWN);
		input.SetPress(mouseButton);
	}
	else
	{
		input.SetEvent(MOUSE_EVENT_UP);
		input.SetRelease(mouseButton);
	}

	TheApp()->ProcessMouseEvent(input);
}

CGALRenderer* theApp = NULL;
CGALRenderer* TheApp()
{
	if (theApp == NULL)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Not CGALRendererInitialized");
	}
	return theApp;
}

CGALRenderer::CGALRenderer()
{
}

CGALRenderer::~CGALRenderer()
{
	for (auto itr = m_pController.begin(); itr != m_pController.end(); itr++)
	{
		delete itr->second;
	}
}

bool CGALRenderer::Initialize()
{
	if (!glfwInit())
	{
		return false;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (m_window == NULL)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	glfwSetCursorPosCallback(m_window, CursorPosCallBack);
	glfwSetMouseButtonCallback(m_window, MouseButtonCallBack);
	glfwSetScrollCallback(m_window, ScrollCallBack);	// mouse wheel;
	glfwSetWindowSizeCallback(m_window, WindowSizeCallBack);

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER] = new CameraController();
	m_pViewport = make_shared<Viewport>();
	m_pViewport->SetPosition(0, 0);
	m_pViewport->Resize(640, 480);

	m_pMouse = make_shared<Mouse>();

	theApp = this;
	return true;
}

void CGALRenderer::SetWorkspace(shared_ptr<Workspace> pWorkspace)
{
	m_pWorkspace = pWorkspace;
}

bool CGALRenderer::Run()
{
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);

	/* OTHER STUFF GOES HERE NEXT */

	shared_ptr<IControllerArgs> args = make_shared<CameraControllerArgs>(
		m_pViewport,
		m_pWorkspace->MainCamera());

	m_pController[CONTROLER_TYPE::CAMERA_CONTROLER]->SetArgs(args);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 400 core");

	while (!glfwWindowShouldClose(m_window))
	{
		
		m_pWorkspace->Invoke();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		m_pWorkspace->ShowProperty();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwPollEvents();
		glfwSwapBuffers(m_window);

	}

	// close GL context and any other GLFW resources
	glfwTerminate();	
	return true;
}

void CGALRenderer::ProcessMouseEvent(const MouseInput& input)
{
	m_pMouse->ApplyMouseInput(input);
	if (input.Event() == MOUSE_EVENT_WHEEL) {
		m_pController[m_CurrentController]->Wheel(*m_pMouse.get());
	}
	else if(input.Event() == MOUSE_EVENT_MOVE)
	{
		m_pController[m_CurrentController]->Move(*m_pMouse.get());
	}
}

void CGALRenderer::ProcessWindowEvent(const WindowEvent& winEvent)
{
	m_pViewport->Resize(winEvent.Size().x, winEvent.Size().y);
}
}