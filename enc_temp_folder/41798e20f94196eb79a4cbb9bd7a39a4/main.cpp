#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>
// program include
#include "Headers/TimeManager.h"
// Shader include
#include "Headers/Shader.h"
// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Headers/Texture.h"
/// Include Loader Model Class
#include "Headers/Model.h"

/*-------------------------AUDIO----------------------------------*/
#include <AL/alut.h>

#define NUM_BUFFERS 2
#define NUM_SOURCES 2
#define NUM_ENVRIONMENTS 1

// Config OpenAL
ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 0.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffers[NUM_BUFFERS];
ALuint sources[NUM_SOURCES];
ALuint enviornment[NUM_ENVRIONMENTS];
// variables para inicializar audios
ALsizei size, freq;
ALenum format;
ALvoid* data;
int ch;
ALboolean loop;


/*-------------------------FIn AUDIO----------------------------------*/

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;
GLFWwindow* window;

//Suma para duplicar la casa
float suma = 65.0f;
float aumentoLuces = 10.0f;
float aumentoLuces2 = 13.0f;
float aumentoLuces3 = 15.0f;

Shader shader;
//Shader de texturizado
Shader shaderTexture;
//Shader con iluminacion solo color
Shader shaderColorLighting;
//Shader con iluminacion y textura
Shader shaderTextureLighting;
// Descomentar
//Shader con materiales
Shader shaderMaterialLighting;
// Descomentar
//Shader con skybox
Shader shaderSkybox;
// Shader con multiples luces
Shader shaderMulLighting;

//std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());
//creacion de elementos para las camaras, camaras para la escena
std::shared_ptr<FirstPersonCamera> cameraHorrorHouseFree(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> cameraChristmastHouseFree(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> cameraHorrorHouseAutomatic(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> cameraChristmastHouseAutomatic(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> cameraOfrenda(new FirstPersonCamera());
std::shared_ptr<FirstPersonCamera> cameraChristmasTree(new FirstPersonCamera());
int cambioCamara = 0;
//--------------------------------------------------

Sphere sphere1(20, 20);
Sphere sphere2(20, 20);
Sphere sphere3(20, 20);
Sphere sphereLamp(20, 20);
Sphere skyboxSphere(20, 20);
Cylinder cylinder1(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Cylinder cylinder3(20, 20, 0.5, 0.5);
Cylinder cylinderMaterials(20, 20, 0.5, 0.5);
Box box1;
Box box;
Box box2;
Box box3;
Box box8, box9, box10, box4, box5, box6, box7;
Box boxMaterials;

//// Models Complex instances
Model modelRock;
Model modelCami;
Model modelRailRoad;
Model ModelAircraft;
Model ModelMesa;
Model ModelEjemplo;
Model modelEclipseChasis;
Model modelEclipseRearWheels;
Model modelEclipseFrontalWheels;
Model modelHeliChasis;
Model modelHeliHeli;
Model modelLambo;
Model modelLamboLeftDor;
Model modelLamboRightDor;
Model modelLamboWheelsFrontal;
Model modelLamboWheelsRear;

Model ModelBell;
Model modelMesa;
Model ModelSilla;
Model ModelBaston;
Model ModelCaballito;
Model ModelCalceta;
Model ModelChimenea;
Model ModelPinoNavidad;
Model ModelEstrella;
Model ModelEsfera;
Model ModelHat;
Model ModelDinosaur;
Model Modeljardinera;
Model ModelNochebuena;
Model ModelRegaloUno;
Model ModelRegaloDos;
Model ModelRosa;

Model ModelSpiderman;
Model ModelTren;
Model ModelTrineo;
Model ModelSofa;
Model ModelSofaP;
Model ModelWC;
Model ModelPinata;
Model ModelPrueba;

Model modelCalabaza;
Model modelflower;
Model modelMango;
Model modelManzana;


//Si jalan
Model modelFantasma;
Model modelSkelet;
Model modelSkull_v3;
Model modelCandlestick;

GLuint skyboxTextureID;
GLuint textureID1, textureID2, textureID3, textureID4,
textureID5, textureID6, textureID7, textureID8,
textureID9, textureID10, textureID11, textureID12,
textureID13, textureID14, textureID15,
textureID16, textureID17, textureID18,
textureID19, textureID20, textureID21,
textureID22, textureID23, textureID24,
textureID25, textureID26, textureID27, textureID28, textureCubeTexture, textureID30, textureID29, textureID31,
//cuarto_1
textureID32, textureID33, textureID34, textureID35, textureID36, textureID37, textureID38, textureID39
//cuarto_2
, textureID40, textureID41, textureID42, textureID43, textureID44, textureID45, textureID46, textureID47, textureID48, textureID49
//cuarto_3
, textureID50, textureID51, textureID52, textureID53, textureID54, textureID55, textureID56, textureID57, textureID58, textureID59, textureID60
//baño
, textureID61, textureID62, textureID63, textureID64, textureID65, textureID66
//cocina
, textureID67, textureID68, textureID69, textureID70, textureID71, textureID72, textureID73, textureID74
//Naciminto
, textureID75, textureID76, textureID77, textureID78, textureID79, textureID81, textureID80, textureID82, textureID83, textureID84, textureID85, textureID86

, textureID87, textureID88, textureID89, textureID90, textureID91, textureID92
//cuadros NAV
, textureID93, textureID94, textureID95, textureID96

, textureID97, textureID98, textureID99, textureID100, textureID101, textureID102
//Pista de aterrizaje
, textureID103

//Dia de Muertos
, textureID104, textureID105, textureID106, textureID107, textureID108, textureID109,
textureID110, textureID111, textureID112,
//nuevas decoraciones
textureID113, textureID114, textureID115, textureID116, textureID117, textureID118, textureID119, textureID120, textureID121,
textureID122, textureID123, textureID124, textureID125, textureID126, textureID127, textureID128, textureID129;


Cylinder torsoR2D2(20, 20, 0.5, 0.5);//se declara el torso de nuevo modelo
Sphere cabezaR2D2(20, 20);//se declara la cabeza del modelo
Sphere articulacionR2D2(20, 20);//se declara la articulacion del modelo
Cylinder brazoR2D2(20, 20, 0.5, 0.5);//se declara el brazo del modelo
Box pieR2D2;//se declara los pies de soporte del modelo

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/ely_darkcity/darkcity_ft.tga",
		"../Textures/ely_darkcity/darkcity_bk.tga",
		"../Textures/ely_darkcity/darkcity_up.tga",
		"../Textures/ely_darkcity/darkcity_dn.tga",
		"../Textures/ely_darkcity/darkcity_rt.tga",
		"../Textures/ely_darkcity/darkcity_lf.tga" };


bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;


float rot1 = 0.0, rot2 = 0.0, rot3 = 0.0, rot4 = 0.0;
float rota1 = 0.0, rota2 = 0.0;///1
float rota3 = 0.0, rota4 = 0.0;///
float d11 = 0, d12 = 0, d13 = 0, d14 = 0;   //Movimiento de los dedos
float r21 = 0, r22 = 0, r23 = 0, r24 = 0;
float desplazamiento = 0.0f;
float rotacionTotal = 0.0f;
float brazoDerecho = 0.0f, brazoIzquierdo = 0.0f;
float rot0 = 0;
float dz = 0;
float rota0 = 0;
float dza = 0;
float rotr20 = 0;
float dzd2 = 0;
bool sentido = true;
double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderTexture.initialize("../Shaders/texturizado_res.vs",
		"../Shaders/texturizado_res.fs");
	shaderColorLighting.initialize("../Shaders/iluminacion_color_res.vs",
		"../Shaders/iluminacion_color_res.fs");
	shaderTextureLighting.initialize("../Shaders/iluminacion_texture_res.vs",
		"../Shaders/iluminacion_texture_res.fs");
	shaderMaterialLighting.initialize("../Shaders/iluminacion_material.vs",
		"../Shaders/iluminacion_material_res.fs");
	shaderSkybox.initialize("../Shaders/cubeTexture.vs",
		"../Shaders/cubeTexture.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_texture_res.vs",
		"../Shaders/multipleLights.fs");

	// Inicializar los buffers VAO, VBO, EBO
	sphere1.init();
	// Método setter que colocar el apuntador al shader
	sphere1.setShader(&shaderColorLighting);
	//Setter para poner el color de la geometria
	sphere1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));
	// Inicializar los buffers VAO, VBO, EBO
	sphere2.init();
	// Método setter que colocar el apuntador al shader
	sphere2.setShader(&shaderColorLighting);
	//Setter para poner el color de la geometria
	sphere2.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	// Inicializar los buffers VAO, VBO, EBO
	sphereLamp.init();
	// Método setter que colocar el apuntador al shader
	sphereLamp.setShader(&shader);
	//Setter para poner el color de la geometria
	sphereLamp.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	cylinder1.init();
	cylinder1.setShader(&shaderColorLighting);
	cylinder1.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));
	cylinder2.init();
	cylinder2.setShader(&shaderMulLighting);
	cylinder3.init();
	cylinder3.setShader(&shaderMulLighting);
	cylinderMaterials.init();
	cylinderMaterials.setShader(&shaderMaterialLighting);
	cylinderMaterials.setColor(glm::vec4(0.3, 0.3, 1.0, 1.0));
	boxMaterials.init();
	boxMaterials.setShader(&shaderMaterialLighting);
	// Inicializacion de la esfera del skybox
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));
	box.init();
	box.setShader(&shaderMulLighting);
	box1.init();
	// Settea el shader a utilizar
	box1.setShader(&shaderMulLighting);
	box1.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
	box2.init();
	box2.setShader(&shaderMulLighting);
	sphere3.init();
	sphere3.setShader(&shaderMulLighting);
	box3.init();
	box3.setShader(&shaderMulLighting);
	box8.init();
	box8.setShader(&shaderMulLighting);
	box9.init();
	box9.setShader(&shaderMulLighting);
	box10.init();
	box10.setShader(&shaderMulLighting);
	box4.init();
	box4.setShader(&shaderMulLighting);
	box5.init();
	box5.setShader(&shaderMulLighting);
	box6.init();
	box6.setShader(&shaderMulLighting);
	box7.init();
	box7.setShader(&shaderMulLighting);


	

	/*Modelos Transporte
	ModelAircraft.loadModel("../models/Aircraft_obj/E 45 Aircraft_obj.obj");
	ModelAircraft.setShader(&shaderMulLighting);

	// Eclipse
	modelEclipseChasis.loadModel("../models/Eclipse/2003eclipse_chasis.obj");
	modelEclipseChasis.setShader(&shaderMulLighting);
	modelEclipseFrontalWheels.loadModel("../models/Eclipse/2003eclipse_frontal_wheels.obj");
	modelEclipseFrontalWheels.setShader(&shaderMulLighting);
	modelEclipseRearWheels.loadModel("../models/Eclipse/2003eclipse_rear_wheels.obj");
	modelEclipseRearWheels.setShader(&shaderMulLighting);
	// Helicopter
	modelHeliChasis.loadModel("../models/Helicopter/Mi_24_chasis.obj");
	modelHeliChasis.setShader(&shaderMulLighting);
	modelHeliHeli.loadModel("../models/Helicopter/Mi_24_heli.obj");
	modelHeliHeli.setShader(&shaderMulLighting);
	// Lamborginhi
	modelLambo.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_chasis.obj");
	modelLambo.setShader(&shaderMulLighting);
	modelLamboLeftDor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_left_dor.obj");
	modelLamboLeftDor.setShader(&shaderMulLighting);
	modelLamboRightDor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_right_dor.obj");
	modelLamboRightDor.setShader(&shaderMulLighting);
	modelLamboWheelsFrontal.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_wheels.obj");
	modelLamboWheelsFrontal.setShader(&shaderMulLighting);
	modelLamboWheelsRear.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_wheels.obj");
	modelLamboWheelsRear.setShader(&shaderMulLighting);
	*/

	/*
	//Modelos de la Casa
	modelMesa.loadModel("../models/table/table.obj");
	modelMesa.setShader(&shaderMulLighting);
	ModelSilla.loadModel("../models/SillaComedor/Chair.obj");
	ModelSilla.setShader(&shaderMulLighting);
	ModelWC.loadModel("../models/toilet/toilet.obj");
	ModelWC.setShader(&shaderMulLighting);
	ModelSofa.loadModel("../models/Navidad/sofa/sofa.obj");
	ModelSofa.setShader(&shaderMulLighting);
	ModelSofaP.loadModel("../models/Navidad/sofap/sofap.obj");
	ModelSofaP.setShader(&shaderMulLighting);
	ModelMesa.loadModel("../models/Wood_Table/Wood_Table.obj");
	ModelMesa.setShader(&shaderMulLighting);
	ModelEjemplo.loadModel("../models/silla/10239_Office_Chair_v1_L3.obj");
	ModelEjemplo.setShader(&shaderMulLighting);
	*/
	//Modelos Otros /Plantas/Roca/Perro/ViasDelTren
	Modeljardinera.loadModel("../models/Navidad/jardinera/jardinera.obj");
	Modeljardinera.setShader(&shaderMulLighting);
	modelRock.loadModel("../models/rock/rock.obj");
	modelRock.setShader(&shaderMulLighting);
	modelCami.loadModel("../models/dog/12228_Dog_v1_L2.obj");
	modelCami.setShader(&shaderMulLighting);
	modelRailRoad.loadModel("../models/railroad/railroad_track.obj");
	modelRailRoad.setShader(&shaderMulLighting);
	/*
	//Cosas de Navidad
	ModelPinata.loadModel("../models/Navidad/pinata/pinata.obj");
	ModelPinata.setShader(&shaderMulLighting);
	
	ModelPinoNavidad.loadModel("../models/Navidad/christmas_tree/Christmas+tree.obj");
	ModelPinoNavidad.setShader(&shaderMulLighting);
	ModelEstrella.loadModel("../models/Navidad/ArbolChido/estrella.obj");
	ModelEstrella.setShader(&shaderMulLighting);
	ModelBell.loadModel("../models/Navidad/bell/11566_Bell_V5_l3.obj");
	ModelBell.setShader(&shaderMulLighting);
	ModelBaston.loadModel("../models/Navidad/baston/baston1.obj");
	ModelBaston.setShader(&shaderMulLighting);
	ModelRegaloUno.loadModel("../models/Navidad/regalo2/regalo.obj");
	ModelRegaloUno.setShader(&shaderMulLighting);
	ModelRegaloDos.loadModel("../models/Navidad/regalo2/regalo.obj");
	ModelRegaloDos.setShader(&shaderMulLighting);
	ModelChimenea.loadModel("../models/Navidad/fuego/13110_Fireplace_v2_l3.obj");
	ModelChimenea.setShader(&shaderMulLighting);
	*/

	//ModelRosa.loadModel("../models/Navidad/rosa/rosa.obj");
	//ModelRosa.setShader(&shaderMulLighting);

	//ModelNochebuena.loadModel("../models/Navidad/nochebuena/nochebuena.obj");
	//ModelNochebuena.setShader(&shaderMulLighting);

	//ModelDinosaur.loadModel("../models/Navidad/Dinosaur/Dinosaur.obj");
	//ModelDinosaur.setShader(&shaderMulLighting);

	//---------------------------------------------------------------------
	//ModelEsfera.loadModel("../models/Navidad/ArbolNavidad/11.obj");
	//ModelEsfera.setShader(&shaderMulLighting);

	/*
	ModelPinoNavidad.loadModel("../models/Navidad/pino/pine_tree.obj");
	ModelPinoNavidad.setShader(&shaderMulLighting);

	ModelTren.loadModel("../models/Navidad/rock/rock.obj");
	ModelTren.setShader(&shaderMulLighting);

	ModelPrueba.loadModel("../models/Navidad/calceta/calceta_roja.obj");
	ModelPrueba.setShader(&shaderMulLighting);
	*/
	/*Fin cosas de Navidad*/

	/*Dia de Muertos
	modelCalabaza;
	modelCandlestick;

	modelMango;
	modelManzana;
	modelSkelet;
	modelSkull_v3;
	*/

	///inicializacion del candelabro
	//modelCalabaza.loadModel("../models/DiaDeMuertos/calabaza/pumpkin.obj");
	//modelCalabaza.setShader(&shaderMulLighting);

	//modelCandlestick.loadModel("../models/DiaDeMuertos/Candlestick/candlestick.obj");
	//modelCandlestick.setShader(&shaderMulLighting);

	//modelMango.loadModel("../models/DiaDeMuertos/Mango/10190_Mango-L3.obj");
	//modelMango.setShader(&shaderMulLighting);

	//modelManzana.loadModel("../models/DiaDeMuertos/manzana/Manzana.obj");
	//modelManzana.setShader(&shaderMulLighting);

	//modelSkull_v3.loadModel("../models/DiaDeMuertos/Skull_v3/12140_Skull_v3_L2.obj");
	//modelSkull_v3.setShader(&shaderMulLighting);


	//Animaciones Dia de Muertos
	/*
	modelFantasma.loadModel("../models/DiaDeMuertos/Ghost/ghost.obj");
	modelFantasma.setShader(&shaderMulLighting);

	modelSkelet.loadModel("../models/DiaDeMuertos/Skull_v3/12140_Skull_v3_L2.obj");
	modelSkelet.setShader(&shaderMulLighting);

	modelCandlestick.loadModel("../models/DiaDeMuertos/Candlestick/candlestick.obj");
	modelCandlestick.setShader(&shaderMulLighting);
	
	*/
	//Animaciones Navidad
	ModelTrineo.loadModel("../models/Navidad/trineo/trineo.obj");
	ModelTrineo.setShader(&shaderMulLighting);


	//Posicion inicial de la camaras**********************
	cameraHorrorHouseFree->setPosition(glm::vec3(55.077236, -2.52848, -25.0336));
	cameraChristmastHouseFree->setPosition(glm::vec3(-3.077236, -2.52848, -86.0336));
	cameraHorrorHouseAutomatic->setPosition(glm::vec3(5.077236, -2.52848, 86.0336));
	cameraChristmastHouseAutomatic->setPosition(glm::vec3(-72.0461, -6.87082, 86.0336));
	cameraOfrenda->setPosition(glm::vec3(0.0, 0.0, 0.0));
	cameraChristmasTree->setPosition(glm::vec3(0.0, 0.0, 0.0));
	//----------------------------------------------------------------

	/*-----------------------Texturas---------------------------------*/
	{
	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	// Definiendo la textura a utilizar
	Texture texture1("../Textures/Muertos/barandal.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	FIBITMAP* bitmap = texture1.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	unsigned char* data = texture1.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID1);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture1.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture2("../Textures/water.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = texture2.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID2);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture2.freeImage(bitmap);

	// Definiendo la textura a utilizar
	//Texture texture3("../Textures/goku.png");
	Texture texture3("../Textures/calle.tif");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture3.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture3.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID3);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID3);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture3.freeImage(bitmap);

	// Definiendo la textura a utilizar
	//Texture texture4("../Textures/texturaLadrillos.jpg");
	Texture texture4("../Textures/calle2.tif");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	// Voltear la imagen
	bitmap = texture4.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = texture4.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureID4);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureID4);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	texture4.freeImage(bitmap);

	/*-----------------------------------------------------------------------------------------------------------*/
	Texture texture5("../Textures/CornerStreet.tif");
	bitmap = texture5.loadImage(true);
	data = texture5.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID5);
	glBindTexture(GL_TEXTURE_2D, textureID5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture5.freeImage(bitmap);

	Texture texture6("../Textures/pared.jpg");
	bitmap = texture6.loadImage(true);
	data = texture6.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID6);
	glBindTexture(GL_TEXTURE_2D, textureID6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture6.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture7("../Textures/piso.jpg");
	bitmap = texture7.loadImage(true);
	data = texture7.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID7);
	glBindTexture(GL_TEXTURE_2D, textureID7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture7.freeImage(bitmap);

	Texture texture8("../Textures/nacimiento/aserrin.jpg");
	bitmap = texture8.loadImage(true);
	data = texture8.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID8);
	glBindTexture(GL_TEXTURE_2D, textureID8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture8.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture9("../Textures/mesa.jpg");
	bitmap = texture9.loadImage(true);
	data = texture9.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID9);
	glBindTexture(GL_TEXTURE_2D, textureID9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture9.freeImage(bitmap);

	Texture texture11("../Textures/espejo.jpg");
	bitmap = texture11.loadImage(true);
	data = texture11.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID11);
	glBindTexture(GL_TEXTURE_2D, textureID11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture11.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture12("../Textures/madera.jpg");
	bitmap = texture12.loadImage(true);
	data = texture12.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID12);
	glBindTexture(GL_TEXTURE_2D, textureID12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture12.freeImage(bitmap);
	//Texture texture13("../Textures/ventana2.png");
	// Definiendo la textura a utilizar

	Texture texture13("../Textures/ventana.png");
	bitmap = texture13.loadImage(true);
	data = texture13.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID13);
	glBindTexture(GL_TEXTURE_2D, textureID13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture13.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture14("../Textures/cesped.jpg");
	bitmap = texture14.loadImage(true);
	data = texture14.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID14);
	glBindTexture(GL_TEXTURE_2D, textureID14);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture14.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture15("../Textures/Muertos/frentePuerta.jpg");
	bitmap = texture15.loadImage(true);
	data = texture15.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID15);
	glBindTexture(GL_TEXTURE_2D, textureID15);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture15.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture16("../Textures/almohada.jpg");
	bitmap = texture16.loadImage(true);
	data = texture16.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID16);
	glBindTexture(GL_TEXTURE_2D, textureID16);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture16.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture17("../Textures/pisoMaderados.jpg");
	bitmap = texture17.loadImage(true);
	data = texture17.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID17);
	glBindTexture(GL_TEXTURE_2D, textureID17);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture17.freeImage(bitmap);

	Texture texture18("../Textures/Muertos/arribaPuertas.png");
	bitmap = texture18.loadImage(true);
	data = texture18.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID18);
	glBindTexture(GL_TEXTURE_2D, textureID18);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture18.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture19("../Textures/compu.jpg");
	bitmap = texture19.loadImage(true);
	data = texture19.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID19);
	glBindTexture(GL_TEXTURE_2D, textureID19);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture19.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture texture20("../Textures/fondo.jpg");
	bitmap = texture20.loadImage(true);
	data = texture20.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID20);
	glBindTexture(GL_TEXTURE_2D, textureID20);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture20.freeImage(bitmap);

	Texture texture24("../Textures/Muertos/ventana.png");
	bitmap = texture24.loadImage(true);
	data = texture24.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID24);
	glBindTexture(GL_TEXTURE_2D, textureID24);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture24.freeImage(bitmap);

	Texture texture25("../Textures/Muertos/paredFea.tif");
	bitmap = texture25.loadImage(true);
	data = texture25.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID25);
	glBindTexture(GL_TEXTURE_2D, textureID25);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture25.freeImage(bitmap);

	Texture texture23("../Textures/barandal.png");
	bitmap = texture23.loadImage(true);
	data = texture23.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID23);
	glBindTexture(GL_TEXTURE_2D, textureID23);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture23.freeImage(bitmap);

	Texture texture22("../Textures/puerta.png");
	bitmap = texture22.loadImage(true);
	data = texture22.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID22);
	glBindTexture(GL_TEXTURE_2D, textureID22);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture22.freeImage(bitmap);


	Texture texture71("../Textures/Muertos/pisoFeo.jpg");
	bitmap = texture71.loadImage(true);
	data = texture71.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID71);
	glBindTexture(GL_TEXTURE_2D, textureID71);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture71.freeImage(bitmap);
	/*------------------------------------------------------------------------------------------------------------*/
	Texture texture30("../Textures/puertaP.png");
	bitmap = texture30.loadImage(true);
	data = texture30.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID30);
	glBindTexture(GL_TEXTURE_2D, textureID30);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture30.freeImage(bitmap);
	//texturas cuarto 1
	//madera
	Texture texture29("../Textures/cuarto_1/madera.jpg");
	bitmap = texture29.loadImage(true);
	data = texture29.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID29);
	glBindTexture(GL_TEXTURE_2D, textureID29);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture29.freeImage(bitmap);
	//puerta del ropero
	Texture texture31("../Textures/cuarto_1/closet_cuarto1.jpg");
	bitmap = texture31.loadImage(true);
	data = texture31.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID31);
	glBindTexture(GL_TEXTURE_2D, textureID31);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture31.freeImage(bitmap);
	//pared verde 
	Texture texture32("../Textures/cuarto_1/pared.png");
	bitmap = texture32.loadImage(true);
	data = texture32.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID32);
	glBindTexture(GL_TEXTURE_2D, textureID32);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture32.freeImage(bitmap);

	//alfombra
	Texture texture33("../Textures/cuarto_1/alfoma.jpg");
	bitmap = texture33.loadImage(true);
	data = texture33.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID33);
	glBindTexture(GL_TEXTURE_2D, textureID33);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture33.freeImage(bitmap);
	//sabana 
	Texture texture34("../Textures/cuarto_1/cama.jpg");
	bitmap = texture34.loadImage(true);
	data = texture34.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID34);
	glBindTexture(GL_TEXTURE_2D, textureID34);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture34.freeImage(bitmap);
	//cuadro_1
	Texture texture35("../Textures/cuarto_1/cuadro_1.jpg");
	bitmap = texture35.loadImage(true);
	data = texture35.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID35);
	glBindTexture(GL_TEXTURE_2D, textureID35);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture35.freeImage(bitmap);
	//cuadro_2
	Texture texture36("../Textures/cuarto_1/cuadro_2.jpg");
	bitmap = texture36.loadImage(true);
	data = texture36.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID36);
	glBindTexture(GL_TEXTURE_2D, textureID36);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture36.freeImage(bitmap);
	//cuadro_3
	Texture texture37("../Textures/cuarto_1/cuadro_3.jpg");
	bitmap = texture37.loadImage(true);
	data = texture37.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID37);
	glBindTexture(GL_TEXTURE_2D, textureID37);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture37.freeImage(bitmap);
	//tv
	Texture texture38("../Textures/cuarto_1/tv.jpg");
	bitmap = texture38.loadImage(true);
	data = texture38.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID38);
	glBindTexture(GL_TEXTURE_2D, textureID38);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture38.freeImage(bitmap);
	//espejo
	Texture texture39("../Textures/cuarto_1/espejo.jpg");
	bitmap = texture39.loadImage(true);
	data = texture39.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID39);
	glBindTexture(GL_TEXTURE_2D, textureID39);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture39.freeImage(bitmap);
	/************************Segundo cuarto***************************************/
	//madera
	Texture texture40("../Textures/cuarto_2/madera.jpg");
	bitmap = texture40.loadImage(true);
	data = texture40.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID40);
	glBindTexture(GL_TEXTURE_2D, textureID40);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture40.freeImage(bitmap);
	//puerta de ropero
	Texture texture41("../Textures/cuarto_2/closet_cuarto2.jpg");
	bitmap = texture41.loadImage(true);
	data = texture41.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID41);
	glBindTexture(GL_TEXTURE_2D, textureID41);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture41.freeImage(bitmap);
	//pared
	Texture texture42("../Textures/cuarto_2/pared.jpg");
	bitmap = texture42.loadImage(true);
	data = texture42.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID42);
	glBindTexture(GL_TEXTURE_2D, textureID42);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture42.freeImage(bitmap);
	//alfombra

	Texture texture43("../Textures/cuarto_2/alfoma.jpg");
	bitmap = texture43.loadImage(true);
	data = texture43.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID43);
	glBindTexture(GL_TEXTURE_2D, textureID43);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture43.freeImage(bitmap);

	//cuadro_1
	Texture texture44("../Textures/cuarto_2/cuadro_1.jpg");
	bitmap = texture44.loadImage(true);
	data = texture44.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID44);
	glBindTexture(GL_TEXTURE_2D, textureID44);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture44.freeImage(bitmap);
	//sabana
	Texture texture45("../Textures/cuarto_2/cama2.jpg");
	bitmap = texture45.loadImage(true);
	data = texture45.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID45);
	glBindTexture(GL_TEXTURE_2D, textureID45);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture45.freeImage(bitmap);


	//cuadro_2
	Texture texture46("../Textures/cuarto_2/cuadro_2.jpg");
	bitmap = texture46.loadImage(true);
	data = texture46.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID46);
	glBindTexture(GL_TEXTURE_2D, textureID46);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture46.freeImage(bitmap);

	//tv
	Texture texture47("../Textures/cuarto_2/tv.jpg");
	bitmap = texture47.loadImage(true);
	data = texture47.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID47);
	glBindTexture(GL_TEXTURE_2D, textureID47);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture47.freeImage(bitmap);

	//cuadro_3
	Texture texture48("../Textures/cuarto_2/cuadro_3.jpg");
	bitmap = texture48.loadImage(true);
	data = texture48.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID48);
	glBindTexture(GL_TEXTURE_2D, textureID48);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture48.freeImage(bitmap);
	/***********************************Cuarto 3 *******************************************/
	//madera
	Texture texture50("../Textures/cuarto_3/madera.jpg");
	bitmap = texture50.loadImage(true);
	data = texture50.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID50);
	glBindTexture(GL_TEXTURE_2D, textureID50);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture50.freeImage(bitmap);
	//closet
	Texture texture51("../Textures/cuarto_3/closet_cuarto3.jpg");
	bitmap = texture51.loadImage(true);
	data = texture51.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID51);
	glBindTexture(GL_TEXTURE_2D, textureID51);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture51.freeImage(bitmap);
	//pared
	Texture texture52("../Textures/cuarto_3/pared.jpg");
	bitmap = texture52.loadImage(true);
	data = texture52.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID52);
	glBindTexture(GL_TEXTURE_2D, textureID52);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture52.freeImage(bitmap);
	//espejo
	Texture texture53("../Textures/cuarto_3/espejo.jpg");
	bitmap = texture53.loadImage(true);
	data = texture53.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID53);
	glBindTexture(GL_TEXTURE_2D, textureID53);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture53.freeImage(bitmap);
	//cama
	Texture texture54("../Textures/cuarto_3/cama.jpg");
	bitmap = texture54.loadImage(true);
	data = texture54.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID54);
	glBindTexture(GL_TEXTURE_2D, textureID54);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture54.freeImage(bitmap);
	//alfoma
	Texture texture55("../Textures/cuarto_3/alfoma.jpg");
	bitmap = texture55.loadImage(true);
	data = texture55.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID55);
	glBindTexture(GL_TEXTURE_2D, textureID55);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture55.freeImage(bitmap);
	//cuadro_1
	Texture texture56("../Textures/cuarto_3/cuadro_1.jpg");
	bitmap = texture56.loadImage(true);
	data = texture56.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID56);
	glBindTexture(GL_TEXTURE_2D, textureID56);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture56.freeImage(bitmap);
	//cuadro_2
	Texture texture57("../Textures/cuarto_3/cuadro_2.jpg");
	bitmap = texture57.loadImage(true);
	data = texture57.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID57);
	glBindTexture(GL_TEXTURE_2D, textureID57);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture57.freeImage(bitmap);
	//cuadro_3
	Texture texture58("../Textures/cuarto_3/cuadro_3.jpg");
	bitmap = texture58.loadImage(true);
	data = texture58.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID58);
	glBindTexture(GL_TEXTURE_2D, textureID58);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture58.freeImage(bitmap);
	//cuadro_4
	Texture texture59("../Textures/cuarto_3/cuadro_4.jpg");
	bitmap = texture59.loadImage(true);
	data = texture59.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID59);
	glBindTexture(GL_TEXTURE_2D, textureID59);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture59.freeImage(bitmap);
	//cuadro_5
	Texture texture60("../Textures/cuarto_3/cuadro_5.jpg");
	bitmap = texture60.loadImage(true);
	data = texture60.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID60);
	glBindTexture(GL_TEXTURE_2D, textureID60);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture60.freeImage(bitmap);


	/****************baño*********************/
	//piso baño
	Texture texture61("../Textures/banio/piso.jpg");
	bitmap = texture61.loadImage(true);
	data = texture61.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID61);
	glBindTexture(GL_TEXTURE_2D, textureID61);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture61.freeImage(bitmap);
	//pared baño

	Texture texture62("../Textures/banio/pared.jpg");
	bitmap = texture62.loadImage(true);
	data = texture62.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID62);
	glBindTexture(GL_TEXTURE_2D, textureID62);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture62.freeImage(bitmap);
	//madera baño

	Texture texture63("../Textures/banio/madera.jpg");
	bitmap = texture63.loadImage(true);
	data = texture63.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID63);
	glBindTexture(GL_TEXTURE_2D, textureID63);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture63.freeImage(bitmap);
	//espejo baño

	Texture texture64("../Textures/banio/espejo.jpg");
	bitmap = texture64.loadImage(true);
	data = texture64.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID64);
	glBindTexture(GL_TEXTURE_2D, textureID64);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture64.freeImage(bitmap);
	/*************************************cocina****************************/
	//madera
	Texture texture67("../Textures/cocina/madera.jpg");
	bitmap = texture67.loadImage(true);
	data = texture67.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID67);
	glBindTexture(GL_TEXTURE_2D, textureID67);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture67.freeImage(bitmap);
	//metal_refri
	Texture texture68("../Textures/cocina/refrigerador_lados.jpg");
	bitmap = texture68.loadImage(true);
	data = texture68.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID68);
	glBindTexture(GL_TEXTURE_2D, textureID68);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture68.freeImage(bitmap);
	//refri_frente
	Texture texture69("../Textures/cocina/refrigerador.jpg");
	bitmap = texture69.loadImage(true);
	data = texture69.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID69);
	glBindTexture(GL_TEXTURE_2D, textureID69);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture69.freeImage(bitmap);
	//estufa encima
	Texture texture70("../Textures/cocina/estufa_sup.jpg");
	bitmap = texture70.loadImage(true);
	data = texture70.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID70);
	glBindTexture(GL_TEXTURE_2D, textureID70);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture70.freeImage(bitmap);

	//pasto nacimeinto
	Texture texture73("../Textures/grass.jpg");
	bitmap = texture73.loadImage(true);
	data = texture73.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID73);
	glBindTexture(GL_TEXTURE_2D, textureID73);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture73.freeImage(bitmap);
	/*------------------------------------------------------------------------------------------------------------*/
	//pasto nacimeinto
	Texture texture74("../Textures/nacimiento/1burro.png");
	bitmap = texture74.loadImage(true);
	data = texture74.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID74);
	glBindTexture(GL_TEXTURE_2D, textureID74);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture74.freeImage(bitmap);

	//pasto nacimeinto
	Texture texture75("../Textures/nacimiento/1pastor.png");
	bitmap = texture75.loadImage(true);
	data = texture75.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID75);
	glBindTexture(GL_TEXTURE_2D, textureID75);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture75.freeImage(bitmap);

	//pasto nacimeinto
	Texture texture76("../Textures/nacimiento/2Jose.png");
	bitmap = texture76.loadImage(true);
	data = texture76.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID76);
	glBindTexture(GL_TEXTURE_2D, textureID76);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture76.freeImage(bitmap);

	//pasto nacimeinto
	Texture texture77("../Textures/nacimiento/2toro.png");
	bitmap = texture77.loadImage(true);
	data = texture77.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID77);
	glBindTexture(GL_TEXTURE_2D, textureID77);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture77.freeImage(bitmap);

	//pasto nacimeinto
	Texture texture78("../Textures/nacimiento/3virgen.png");
	bitmap = texture78.loadImage(true);
	data = texture78.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID78);
	glBindTexture(GL_TEXTURE_2D, textureID78);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture78.freeImage(bitmap);

	//pasto nacimeinto
	Texture texture79("../Textures/nacimiento/ninoAnimado.png");
	bitmap = texture79.loadImage(true);
	data = texture79.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID79);
	glBindTexture(GL_TEXTURE_2D, textureID79);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture79.freeImage(bitmap);


	//pasto nacimeinto
	Texture texture80("../Textures/nacimiento/4pastor.png");
	bitmap = texture80.loadImage(true);
	data = texture80.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID80);
	glBindTexture(GL_TEXTURE_2D, textureID80);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture80.freeImage(bitmap);

	Texture texture81("../Textures/nacimiento/5pastor.png");
	bitmap = texture81.loadImage(true);
	data = texture81.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID81);
	glBindTexture(GL_TEXTURE_2D, textureID81);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture81.freeImage(bitmap);

	Texture texture82("../Textures/nacimiento/rey1.png");
	bitmap = texture82.loadImage(true);
	data = texture82.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID82);
	glBindTexture(GL_TEXTURE_2D, textureID82);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture82.freeImage(bitmap);

	Texture texture83("../Textures/nacimiento/rey2.png");
	bitmap = texture83.loadImage(true);
	data = texture83.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID83);
	glBindTexture(GL_TEXTURE_2D, textureID83);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture83.freeImage(bitmap);

	Texture texture84("../Textures/nacimiento/rey3.png");
	bitmap = texture84.loadImage(true);
	data = texture84.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID84);
	glBindTexture(GL_TEXTURE_2D, textureID84);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture84.freeImage(bitmap);

	Texture texture85("../Textures/nacimiento/paja.png");
	bitmap = texture85.loadImage(true);
	data = texture85.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID85);
	glBindTexture(GL_TEXTURE_2D, textureID85);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture85.freeImage(bitmap);

	Texture texture86("../Textures/nacimiento/fonfoGra.png");
	bitmap = texture86.loadImage(true);
	data = texture86.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID86);
	glBindTexture(GL_TEXTURE_2D, textureID86);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture86.freeImage(bitmap);

	Texture texture87("../Textures/nacimiento/fondoNac.png");
	bitmap = texture87.loadImage(true);
	data = texture87.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID87);
	glBindTexture(GL_TEXTURE_2D, textureID87);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture87.freeImage(bitmap);

	Texture texture88("../Textures/nacimiento/fondoGre.png");
	bitmap = texture88.loadImage(true);
	data = texture88.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID88);
	glBindTexture(GL_TEXTURE_2D, textureID88);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture88.freeImage(bitmap);

	Texture texture89("../Textures/nacimiento/1pollo.png");
	bitmap = texture89.loadImage(true);
	data = texture89.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID89);
	glBindTexture(GL_TEXTURE_2D, textureID89);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture89.freeImage(bitmap);

	Texture texture90("../Textures/nacimiento/2siervo.png");
	bitmap = texture90.loadImage(true);
	data = texture90.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID90);
	glBindTexture(GL_TEXTURE_2D, textureID90);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture90.freeImage(bitmap);

	Texture texture91("../Textures/nacimiento/3conejo.png");
	bitmap = texture91.loadImage(true);
	data = texture91.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID91);
	glBindTexture(GL_TEXTURE_2D, textureID91);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture91.freeImage(bitmap);
	////Libre
	Texture texture92("../Textures/cuadros/1.jfif");
	bitmap = texture92.loadImage(true);
	data = texture92.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID92);
	glBindTexture(GL_TEXTURE_2D, textureID92);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture92.freeImage(bitmap);

	////Libre
	Texture texture93("../Textures/cuadros/2.jfif");
	bitmap = texture93.loadImage(true);
	data = texture93.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID93);
	glBindTexture(GL_TEXTURE_2D, textureID93);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture93.freeImage(bitmap);

	////Libre
	Texture texture94("../Textures/cuadros/3.jfif");
	bitmap = texture94.loadImage(true);
	data = texture94.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID94);
	glBindTexture(GL_TEXTURE_2D, textureID94);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture94.freeImage(bitmap);

	////Libre
	Texture texture95("../Textures/cuadros/4.jfif");
	bitmap = texture95.loadImage(true);
	data = texture95.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID95);
	glBindTexture(GL_TEXTURE_2D, textureID95);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture95.freeImage(bitmap);

	////Libre
	Texture texture96("../Textures/cuadros/5.jfif");
	bitmap = texture96.loadImage(true);
	data = texture96.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID96);
	glBindTexture(GL_TEXTURE_2D, textureID96);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture96.freeImage(bitmap);

	////Libre
	Texture texture97("../Textures/cuadros/cuadro1.jpg");
	bitmap = texture97.loadImage(true);
	data = texture97.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID97);
	glBindTexture(GL_TEXTURE_2D, textureID97);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture97.freeImage(bitmap);

	////Libre
	Texture texture98("../Textures/cuadros/cuadro2.jpg");
	bitmap = texture98.loadImage(true);
	data = texture98.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID98);
	glBindTexture(GL_TEXTURE_2D, textureID98);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture98.freeImage(bitmap);


	Texture texture99("../Textures/cuadros/peliNav.jpg");
	bitmap = texture99.loadImage(true);
	data = texture99.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID99);
	glBindTexture(GL_TEXTURE_2D, textureID99);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture99.freeImage(bitmap);

	////Libre ------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>
	Texture texture100("../Textures/cuadros/peliNav2.jpg");
	bitmap = texture100.loadImage(true);
	data = texture100.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID100);
	glBindTexture(GL_TEXTURE_2D, textureID100);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture100.freeImage(bitmap);

	////Libre
	Texture texture101("../Textures/cuadros/tv.jpg");
	bitmap = texture101.loadImage(true);
	data = texture101.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID101);
	glBindTexture(GL_TEXTURE_2D, textureID101);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture101.freeImage(bitmap);

	////Libre
	Texture texture102("../Textures/nacimiento/rosca.jpg");
	bitmap = texture102.loadImage(true);
	data = texture102.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID102);
	glBindTexture(GL_TEXTURE_2D, textureID102);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture102.freeImage(bitmap);

	//pista helicoptero 103
	Texture texture103("../Textures/logo.png");
	bitmap = texture103.loadImage(true);
	data = texture103.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID103);
	glBindTexture(GL_TEXTURE_2D, textureID103);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture103.freeImage(bitmap);

	//papel picado-rojo 104
	Texture texture104("../Textures/deco_muertos/pp_1.png");
	bitmap = texture104.loadImage(true);
	data = texture104.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID104);
	glBindTexture(GL_TEXTURE_2D, textureID104);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture104.freeImage(bitmap);
	//papel picado-verde 105
	Texture texture105("../Textures/deco_muertos/pp_2.png");
	bitmap = texture105.loadImage(true);
	data = texture105.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID105);
	glBindTexture(GL_TEXTURE_2D, textureID105);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture105.freeImage(bitmap);
	//papel picado-azul 106
	Texture texture106("../Textures/deco_muertos/pp_3.png");
	bitmap = texture106.loadImage(true);
	data = texture106.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID106);
	glBindTexture(GL_TEXTURE_2D, textureID106);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture106.freeImage(bitmap);
	//papel picado-rosa 107
	Texture texture107("../Textures/deco_muertos/pp_4.png");
	bitmap = texture107.loadImage(true);
	data = texture107.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID107);
	glBindTexture(GL_TEXTURE_2D, textureID107);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture107.freeImage(bitmap);
	//papel picado-morado 108
	Texture texture108("../Textures/deco_muertos/pp_5.png");
	bitmap = texture108.loadImage(true);
	data = texture108.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID108);
	glBindTexture(GL_TEXTURE_2D, textureID108);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture108.freeImage(bitmap);
	//papel picado-amarillo 109
	Texture texture109("../Textures/deco_muertos/pp_6.png");
	bitmap = texture109.loadImage(true);
	data = texture109.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID109);
	glBindTexture(GL_TEXTURE_2D, textureID109);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture109.freeImage(bitmap);
	//papel picado-completo 110
	Texture texture110("../Textures/deco_muertos/pp_largo.png");
	bitmap = texture110.loadImage(true);
	data = texture110.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID110);
	glBindTexture(GL_TEXTURE_2D, textureID110);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture110.freeImage(bitmap);

	/*
	//flores 113
	Texture texture113("../Textures/deco_muertos/flores.png");
	bitmap = texture113.loadImage(true);
	data = texture113.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID113);
	glBindTexture(GL_TEXTURE_2D, textureID113);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture113.freeImage(bitmap);
  */

  /*segundo cuarto de muertos*/

	//madera
	Texture texture114("../Textures/cuarto_2_m/madera.jpg");
	bitmap = texture114.loadImage(true);
	data = texture114.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID114);
	glBindTexture(GL_TEXTURE_2D, textureID114);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture114.freeImage(bitmap);


	//puerta de ropero
	Texture texture115("../Textures/cuarto_2_m/closet_cuarto2.jpg");
	bitmap = texture115.loadImage(true);
	data = texture115.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID115);
	glBindTexture(GL_TEXTURE_2D, textureID115);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture115.freeImage(bitmap);


	//sabana
	Texture texture116("../Textures/cuarto_2_m/alfoma.jpg");
	bitmap = texture116.loadImage(true);
	data = texture116.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID116);
	glBindTexture(GL_TEXTURE_2D, textureID116);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture116.freeImage(bitmap);

	/*Primer cuarto de muertos*/
	//alfombra
	Texture texture117("../Textures/cuarto_1_m/alfoma.png");
	bitmap = texture117.loadImage(true);
	data = texture117.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID117);
	glBindTexture(GL_TEXTURE_2D, textureID117);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture117.freeImage(bitmap);

	//espejo
	Texture texture118("../Textures/cuarto_1_m/espejo.jpg");
	bitmap = texture118.loadImage(true);
	data = texture118.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID118);
	glBindTexture(GL_TEXTURE_2D, textureID118);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture118.freeImage(bitmap);

	//cuadro 1
	Texture texture120("../Textures/cuarto_1_m/cuadro_1.jpg");
	bitmap = texture120.loadImage(true);
	data = texture120.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID120);
	glBindTexture(GL_TEXTURE_2D, textureID120);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture120.freeImage(bitmap);

	//puerta de ropero
	Texture texture119("../Textures/cuarto_1_m/closet_cuarto1.jpg");
	bitmap = texture119.loadImage(true);
	data = texture119.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID119);
	glBindTexture(GL_TEXTURE_2D, textureID119);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture119.freeImage(bitmap);

	//pan dia de muertos
	Texture texture121("../Textures/deco_muertos/pan.jpg");
	bitmap = texture121.loadImage(true);
	data = texture121.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID121);
	glBindTexture(GL_TEXTURE_2D, textureID121);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture121.freeImage(bitmap);

	//rojo
	Texture texture122("../Textures/deco_muertos/rojo.jpg");
	bitmap = texture122.loadImage(true);
	data = texture122.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID122);
	glBindTexture(GL_TEXTURE_2D, textureID122);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture122.freeImage(bitmap);

	//mama coco
	Texture texture123("../Textures/deco_muertos/coco.jpg");
	bitmap = texture123.loadImage(true);
	data = texture123.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID123);
	glBindTexture(GL_TEXTURE_2D, textureID123);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture123.freeImage(bitmap);

	//bob
	Texture texture124("../Textures/deco_muertos/bob.jpg");
	bitmap = texture124.loadImage(true);
	data = texture124.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID124);
	glBindTexture(GL_TEXTURE_2D, textureID124);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture124.freeImage(bitmap);
	//bill muray
	Texture texture125("../Textures/deco_muertos/bill.jpg");
	bitmap = texture125.loadImage(true);
	data = texture125.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID125);
	glBindTexture(GL_TEXTURE_2D, textureID125);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture125.freeImage(bitmap);


	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
			skyboxTexture = Texture(fileNames[i]);
			FIBITMAP* bitmap = skyboxTexture.loadImage(true);
			unsigned char* data = skyboxTexture.convertToData(bitmap, imageWidth,
				imageHeight);
			if (data) {
				glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
					GL_BGRA, GL_UNSIGNED_BYTE, data);
			}
			else
				std::cout << "Failed to load texture" << std::endl;
			skyboxTexture.freeImage(bitmap);
		}

	}

	/*-------------------------AUDIO----------------------------------*/
	// OpenAL init
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // Limpiamos los errores previos de OpenAL
	if (alGetError() != AL_NO_ERROR) {
		printf("Error al crear los buffers");
		exit(1);
	}
	else
		printf("Se crearon los buffers");
	alGenBuffers(NUM_BUFFERS, buffers);
	buffers[0] = alutCreateBufferFromFile("../sounds/fondo.wav");
	buffers[1] = alutCreateBufferFromFile("../sounds/fondo.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("Error al crear los buffers %d", errorAlut);
		exit(2);
	}
	else
		printf("Se crearon los buffers");
	glGetError();
	alGenSources(NUM_SOURCES, sources);
	if (alutGetError() != AL_NO_ERROR) {
		printf("Error al crear las fuentes de sonidos");
		exit(2);
	}
	else
		printf("Se crearon las fuentes de sonido");
	//alSourcef(sources[0], AL_PITCH, 0.7f);
	alSourcef(sources[0], AL_PITCH, 1.0f);
	//alSourcef(sources[0], AL_GAIN, 0.1f);
	alSourcef(sources[0], AL_GAIN, 1.0f);
	alSourcefv(sources[0], AL_VELOCITY, source0Vel);
	alSourcefv(sources[0], AL_POSITION, source0Pos);
	alSourcei(sources[0], AL_BUFFER, buffers[0]);
	alSourcei(sources[0], AL_LOOPING, AL_TRUE);
	alSourcei(sources[0], AL_MAX_DISTANCE, 2000);
	alSourcef(sources[1], AL_PITCH, 0.7f);
	alSourcef(sources[1], AL_GAIN, 0.1f);
	alSourcefv(sources[1], AL_VELOCITY, source0Vel);
	alSourcefv(sources[1], AL_POSITION, source0Pos);
	alSourcei(sources[1], AL_BUFFER, buffers[0]);
	alSourcei(sources[1], AL_LOOPING, AL_TRUE);
	alSourcei(sources[1], AL_MAX_DISTANCE, 2000);
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// Eliminar los shader y buffers creados. Destrucción de los VAO, EBO, VBO
	sphere1.destroy();
	cylinder1.destroy();
	box1.destroy();
	box.destroy();
	box8.destroy();
	box9.destroy();
	box10.destroy();
	box2.destroy();
	box3.destroy();
	box4.destroy();
	box5.destroy();
	box6.destroy();
	box7.destroy();

	torsoR2D2.destroy();
	sphere3.destroy();
	cabezaR2D2.destroy();
	articulacionR2D2.destroy();
	brazoR2D2.destroy();
	pieR2D2.destroy();

	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderMaterialLighting.destroy();
	shaderColorLighting.destroy();
	shaderSkybox.destroy();
	shaderTexture.destroy();
	shaderTextureLighting.destroy();
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		case GLFW_KEY_0:
			cambioCamara = 0;//camara libre de la casa de terror
			break;
		case GLFW_KEY_1:
			cambioCamara = 1;//camara libre de la casa de navidad
			break;
		case GLFW_KEY_2:
			cambioCamara = 2;//camara recorrido de la casa de terror
			break;
		case GLFW_KEY_3:
			cambioCamara = 3;//camara recorrido de la casa de navidad
			break;
		case GLFW_KEY_4:
			cambioCamara = 4;//camara en frente de la ofrenda de navidad
			break;
		case GLFW_KEY_5:
			cambioCamara = 5;//camara en frente del arbol de navidad
			break;
		case GLFW_KEY_9:
			std::cout << cameraHorrorHouseFree->getPosition().x << " , " << cameraHorrorHouseFree->getPosition().y
				<< " , " << cameraHorrorHouseFree->getPosition().z << std::endl;
		default:
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}
	TimeManager::Instance().CalculateFrameRate(false);
	deltaTime = TimeManager::Instance().DeltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (cambioCamara == 0) {
			cameraHorrorHouseFree->moveFrontCamera(true, deltaTime);
		}
		else if (cambioCamara == 1) {
			cameraChristmastHouseFree->moveFrontCamera(true, deltaTime);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (cambioCamara == 0) {
			cameraHorrorHouseFree->moveFrontCamera(false, deltaTime);
		}
		else if (cambioCamara == 1) {
			cameraChristmastHouseFree->moveFrontCamera(false, deltaTime);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (cambioCamara == 0) {
			cameraHorrorHouseFree->moveRightCamera(false, deltaTime);
		}
		else if (cambioCamara == 1) {
			cameraChristmastHouseFree->moveRightCamera(false, deltaTime);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (cambioCamara == 0) {
			cameraHorrorHouseFree->moveRightCamera(true, deltaTime);
		}
		else if (cambioCamara == 1) {
			cameraChristmastHouseFree->moveRightCamera(true, deltaTime);
		}
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (cambioCamara == 0) {
			cameraHorrorHouseFree->mouseMoveCamera(offsetX, offsetY, 0.01);
		}
		else if (cambioCamara == 1) {
			cameraChristmastHouseFree->mouseMoveCamera(offsetX, offsetY, 0.01);
		}
	}
	offsetX = 0;
	offsetY = 0;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)///3
		sentido = false;///1
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && sentido)
		rot1 += 0.1;///1
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !sentido)
		rot1 -= 0.1;///3
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && sentido)
		rot2 += 0.1;///1
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && sentido)
		rot3 += 0.1;///2
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && sentido)
		rot4 += 0.1;///2
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)///3
		sentido = true;///1
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && sentido)
		rota1 += 0.1;///1
	else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && !sentido)
		rota1 -= 0.1;///3
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && sentido)
		rota2 += 0.1;///1
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && sentido)
		rota3 += 0.1;///2
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && sentido)
		rota4 += 0.1;///2
	//Movimiento de los dedos:
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && sentido)
		d11 += 0.01;///2
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && sentido)
		d12 -= 0.01;///2
	//Se mueva completo:
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)///3
		rot0 = 0.01;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)///3
		rot0 = -0.01;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)///3
		dz = 0.01;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)///3
		dz = -0.01;
	//R2D2
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)///3
		rota0 = 0.01;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)///3
		rota0 = -0.01;
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)///3
		dza = 0.01;
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)///3
		dza = -0.01;
	/*----------------AUDIO---------------*/
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		alSourcePlay(sources[0]);
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		alSourcePlay(sources[1]);
	/*----------------FIn AUDIO---------------*/
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {

	bool psi = true;
	glm::mat4 modelR2D2 = glm::mat4(1.0f);//referencia para el nuevo modelo
	glm::mat4 model = glm::mat4(1.0f);

	float offX = 0.0;
	float angle = 0.0;
	float ratio = 5.0;
	glm::mat4 matrixModelAircraft = glm::mat4(1.0);
	matrixModelAircraft = glm::translate(matrixModelAircraft, glm::vec3(-73.0, -14.0, -82.0));
	int state = 0;
	int state2 = 4;

	float offsetAircraftAdvance = 0;
	float offsetAircraftAdvanceII = 0;
	float offsetAircraftRot = 0;
	float luces = 0.00;
	float luces2 = 5.00;

	glm::mat4 Helicopter = glm::mat4(1.0);
	Helicopter = glm::translate(Helicopter, glm::vec3(-35.0, 31.0, 55.0));
	Helicopter = glm::scale(Helicopter, glm::vec3(3.0, 3.0, 3.00));
	Helicopter = glm::rotate(Helicopter, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
	float pos = -20;
	float x = 18.0;
	float xx = 25.0;
	//////((///////////////////////////
	model = glm::translate(model, glm::vec3(0.0, 1.5, 0.0));
	glm::mat4 modelMatrixEclipse = glm::mat4(1.0f);
	modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(-73.0, -14.0, -82.0));
	modelMatrixEclipse = glm::scale(modelMatrixEclipse, glm::vec3(3.0, 3.0, 3.00));
	float advanceCount = 0.0;
	float rotCount = 0.0;
	float rotWheelsX = 0.0;
	float rotWheelsY = 0.0;
	float rotWheelsXlamb = 0.0;
	glm::mat4 modelMatrixHeli = glm::mat4(1.0f);
	modelMatrixHeli = glm::translate(modelMatrixHeli, glm::vec3(-35.0, 31.0, 55.0));
	modelMatrixHeli = glm::scale(modelMatrixHeli, glm::vec3(3.0, 3.0, 3.00));
	modelMatrixHeli = glm::rotate(modelMatrixHeli, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
	float rotHelHelYStop = 5.0;
	float rotHelHelY = 0.0;
	int stateDoor = 0;
	float dorRotCount = 0.0;

	glm::mat4 modelMatrixDart = glm::mat4(1.0f);
	modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(3.0, 0.0, 20.0));
	modelMatrixDart = glm::scale(modelMatrixDart, glm::vec3(0.5, 0.5, 0.5));

	int stateHouseRecorrido = 0;
	float recorridoCamara = 0;
	float giroCamaraY = 0;

	
	int stadoFantasma = 0;
	float advanceCountFantasma = 0.0;
	float offsetFantasmaRot = 0.0;

	int stadoCandelabro = 0;
	float advanceCountCandelabro = 0.0;
	float offsetCandelabroRot = 0.0;
	float	posicionCandelabroY = 0.0f,
	posicionCandelabroInicialY = 0.0f,
	velocidadInicialCandelabro = 1.0f,
	anguloCandelabro = 30.0f * 3.1416 / 180.0,//angulo del salto
	gravedad = 9.81f, //gravedad
	tiempoCandelabro = 0.0f;//tiempo

	int stadoCraneo = 0;
	float advanceCountCraneo = 0.0;
	float offsetCraneoRot = 0.0;

	int stateTrineo = 0;
	float advanceCountTrineo = 0.0;
	float offsetTrineoRot = 0.0;
	//Fantasma
	glm::mat4 modelMatrixFantasma = glm::mat4(1.0);
	modelMatrixFantasma = glm::translate(modelMatrixFantasma, glm::vec3(65.0, 0.0, -35.0));

	//Candelabro
	glm::mat4 modelMatrixCandelabro = glm::mat4(1.0);
	modelMatrixCandelabro = glm::translate(modelMatrixCandelabro, glm::vec3(65.0, -20.0, -25.0));
	
	//Craneo
	glm::mat4 modelMatrixCraneo = glm::mat4(1.0);
	modelMatrixCraneo = glm::translate(modelMatrixCraneo, glm::vec3(70.0, -13.0, -40.0));
	modelMatrixCraneo = glm::rotate(modelMatrixCraneo, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	
	//Trineo
	glm::mat4 modelMatrixTrineo = glm::mat4(1.0);
	modelMatrixTrineo = glm::translate(modelMatrixTrineo, glm::vec3(-8.0, 1.1, -40.0));
	//modelMatrixTrineo = glm::rotate(modelMatrixTrineo, glm::radians(-90.0f), glm::vec3(1, 0, 0));

	/////////////////////////
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);
		//segun la camara, sera la matriz de vista
		glm::mat4 view;
		switch (cambioCamara) {
		case 0:
			view = cameraHorrorHouseFree->getViewMatrix();
			break;
		case 1:
			view = cameraChristmastHouseFree->getViewMatrix();
			break;
		case 2:
			view = cameraHorrorHouseAutomatic->getViewMatrix();
			break;
		case 3:
			view = cameraChristmastHouseAutomatic->getViewMatrix();
			break;
		case 4:
			view = cameraOfrenda->getViewMatrix();
			break;
		case 5:
			view = cameraChristmasTree->getViewMatrix();
			break;
		default:
			view = cameraHorrorHouseFree->getViewMatrix();
			break;
		}

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con solo textura
		shaderTexture.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion solo color
		shaderColorLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderColorLighting.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion con textura
		shaderTextureLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTextureLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con iluminacion con material
		shaderMaterialLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMaterialLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
			glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
			glm::value_ptr(view));

		// Propiedades de la luz para objetos con color
		//	segun la camra seleccionada, se cargar el shader en la escena
		switch (cambioCamara) {
		case 0:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		case 1:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseFree->getPosition()));
			break;
		case 2:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseAutomatic->getPosition()));
			break;
		case 3:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseAutomatic->getPosition()));
			break;
		case 4:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraOfrenda->getPosition()));
			break;
		case 5:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmasTree->getPosition()));
			break;
		default:
			shaderColorLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		}
		shaderColorLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		//	segun la camra seleccionada, se cargar el shader en la escena
		switch (cambioCamara) {
		case 0:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		case 1:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseFree->getPosition()));
			break;
		case 2:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseAutomatic->getPosition()));
			break;
		case 3:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseAutomatic->getPosition()));
			break;
		case 4:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraOfrenda->getPosition()));
			break;
		case 5:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmasTree->getPosition()));
			break;
		default:
			shaderTextureLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		}
		shaderTextureLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		//	segun la camra seleccionada, se cargar el shader en la escena
		switch (cambioCamara) {
		case 0:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		case 1:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseFree->getPosition()));
			break;
		case 2:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseAutomatic->getPosition()));
			break;
		case 3:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseAutomatic->getPosition()));
			break;
		case 4:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraOfrenda->getPosition()));
			break;
		case 5:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmasTree->getPosition()));
			break;
		default:
			shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		}
		shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

		// Propiedades de la luz para objetos con multiples luces
		///////////////////////////////////////////////////////Intensidad de luz
		//	segun la camra seleccionada, se cargar el shader en la escena
		switch (cambioCamara) {
		case 0:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		case 1:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseFree->getPosition()));
			break;
		case 2:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseAutomatic->getPosition()));
			break;
		case 3:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmastHouseAutomatic->getPosition()));
			break;
		case 4:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraOfrenda->getPosition()));
			break;
		case 5:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraChristmasTree->getPosition()));
			break;
		default:
			shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			break;
		}
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 1.0)));
		//SpotLight
		shaderMulLighting.setInt("spotLightCount", 1);
		//	segun la camra seleccionada, se cargar el shader en la escena
		switch (cambioCamara) {
		case 0:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraHorrorHouseFree->getFront()));
			break;
		case 1:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraChristmastHouseFree->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraChristmastHouseFree->getFront()));
			break;
		case 2:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraHorrorHouseAutomatic->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraHorrorHouseAutomatic->getFront()));
			break;
		case 3:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraChristmastHouseAutomatic->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraChristmastHouseAutomatic->getFront()));
			break;
		case 4:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraOfrenda->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraOfrenda->getFront()));
			break;
		case 5:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraChristmasTree->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraChristmasTree->getFront()));
			break;
		default:
			shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(cameraHorrorHouseFree->getPosition()));
			shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(cameraHorrorHouseFree->getFront()));
			break;
		}
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
		shaderMulLighting.setFloat("spotLights[0].cuadratic", 0.05);
		if (luces >= 3.00) {
			luces = 0.00;
			luces2 = 3.00;
		}
		else {
			/*Luces*/
		// Esto es para la luces pointlights
		//Numero de luces a utilizar de tipo poinlights=3
			shaderMulLighting.setInt("pointLightCount", 104);   //Multiple Light .fs
			//01Verde
			shaderMulLighting.setVectorFloat3("pointLights[0].position", glm::value_ptr((glm::vec3(-14.4, 11, 4.0))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[0].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[0].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[0].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[0].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[0].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//02 Roja
			shaderMulLighting.setVectorFloat3("pointLights[1].position", glm::value_ptr((glm::vec3(-14.4, 11, 4.7))));
			shaderMulLighting.setVectorFloat3("pointLights[1].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[1].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[1].constant", luces2);
			shaderMulLighting.setFloat("pointLights[1].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[1].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//03 Azul
			shaderMulLighting.setVectorFloat3("pointLights[2].position", glm::value_ptr((glm::vec3(-14.4, 11, 5.4))));
			shaderMulLighting.setVectorFloat3("pointLights[2].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[2].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[2].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[2].constant", luces);
			shaderMulLighting.setFloat("pointLights[2].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[2].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//04 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[3].position", glm::value_ptr((glm::vec3(-14.4, 11, 6.1))));
			shaderMulLighting.setVectorFloat3("pointLights[3].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[3].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[3].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[3].constant", luces2);
			shaderMulLighting.setFloat("pointLights[3].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[3].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//05  Morada
			shaderMulLighting.setVectorFloat3("pointLights[4].position", glm::value_ptr((glm::vec3(-14.4, 11, 6.10))));
			shaderMulLighting.setVectorFloat3("pointLights[4].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[4].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.1)));
			shaderMulLighting.setVectorFloat3("pointLights[4].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("pointLights[4].constant", luces);
			shaderMulLighting.setFloat("pointLights[4].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[4].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//06Verde
			shaderMulLighting.setVectorFloat3("pointLights[5].position", glm::value_ptr((glm::vec3(-14.4, 11, 7.5))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[5].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[5].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[5].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[5].constant", luces2); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[5].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[5].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//07 Roja
			shaderMulLighting.setVectorFloat3("pointLights[6].position", glm::value_ptr((glm::vec3(-14.4, 11, 8.2))));
			shaderMulLighting.setVectorFloat3("pointLights[6].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[6].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[6].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[6].constant", luces);
			shaderMulLighting.setFloat("pointLights[6].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[6].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//08 Azul
			shaderMulLighting.setVectorFloat3("pointLights[7].position", glm::value_ptr((glm::vec3(-14.4, 11, 8.9))));
			shaderMulLighting.setVectorFloat3("pointLights[7].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[7].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[7].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[7].constant", luces2);
			shaderMulLighting.setFloat("pointLights[7].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[7].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//09 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[8].position", glm::value_ptr((glm::vec3(-14.4, 11, 9.6))));
			shaderMulLighting.setVectorFloat3("pointLights[8].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[8].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[8].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[8].constant", luces);
			shaderMulLighting.setFloat("pointLights[8].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[8].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//010  Morada
			shaderMulLighting.setVectorFloat3("pointLights[9].position", glm::value_ptr((glm::vec3(-14.4, 11, 10.3))));
			shaderMulLighting.setVectorFloat3("pointLights[9].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[9].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.1)));
			shaderMulLighting.setVectorFloat3("pointLights[9].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("pointLights[9].constant", luces2);
			shaderMulLighting.setFloat("pointLights[9].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[9].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//////LUZ nueva 11
			shaderMulLighting.setVectorFloat3("pointLights[10].position", glm::value_ptr((glm::vec3(-14.4, 11, 11.0))));
			shaderMulLighting.setVectorFloat3("pointLights[10].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[10].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[10].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[10].constant", luces);
			shaderMulLighting.setFloat("pointLights[10].linear", 1.14);
			shaderMulLighting.setFloat("pointLights[10].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			/*Luces Brandal Arriba*/
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			//01Verde
			shaderMulLighting.setVectorFloat3("pointLights[11].position", glm::value_ptr((glm::vec3(-14.4, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[11].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[11].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[11].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[11].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[11].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[11].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//02 Roja
			shaderMulLighting.setVectorFloat3("pointLights[12].position", glm::value_ptr((glm::vec3(-13.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[12].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[12].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[12].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[12].constant", luces2);
			shaderMulLighting.setFloat("pointLights[12].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[12].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//03 Azul
			shaderMulLighting.setVectorFloat3("pointLights[13].position", glm::value_ptr((glm::vec3(-13.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[13].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[13].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[13].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[13].constant", luces);
			shaderMulLighting.setFloat("pointLights[13].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[13].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//04 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[14].position", glm::value_ptr((glm::vec3(-12.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[14].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[14].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[14].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[14].constant", luces2);
			shaderMulLighting.setFloat("pointLights[14].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[14].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//06Verde
			shaderMulLighting.setVectorFloat3("pointLights[15].position", glm::value_ptr((glm::vec3(-11.4, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[15].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[15].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[15].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[15].constant", luces2); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[15].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[15].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//07 Roja
			shaderMulLighting.setVectorFloat3("pointLights[16].position", glm::value_ptr((glm::vec3(-10.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[16].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[16].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[16].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[16].constant", luces);
			shaderMulLighting.setFloat("pointLights[16].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[16].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//08 Azul
			shaderMulLighting.setVectorFloat3("pointLights[17].position", glm::value_ptr((glm::vec3(-10.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[17].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[17].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[17].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[17].constant", luces2);
			shaderMulLighting.setFloat("pointLights[17].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[17].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//09 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[18].position", glm::value_ptr((glm::vec3(-9.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[18].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[18].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[18].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[18].constant", luces);
			shaderMulLighting.setFloat("pointLights[18].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[18].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//////LUZ nueva 22
			shaderMulLighting.setVectorFloat3("pointLights[19].position", glm::value_ptr((glm::vec3(-8.5, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[19].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[19].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[19].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[19].constant", luces);
			shaderMulLighting.setFloat("pointLights[19].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[19].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			//22Verde
			shaderMulLighting.setVectorFloat3("pointLights[20].position", glm::value_ptr((glm::vec3(-8.0, 15.1, -45.10))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[20].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[20].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[20].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[20].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[20].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[20].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//21 Roja
			shaderMulLighting.setVectorFloat3("pointLights[21].position", glm::value_ptr((glm::vec3(-7.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[21].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[21].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[21].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[21].constant", luces2);
			shaderMulLighting.setFloat("pointLights[21].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[21].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//22 Azul
			shaderMulLighting.setVectorFloat3("pointLights[22].position", glm::value_ptr((glm::vec3(-6.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[22].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[22].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[22].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[22].constant", luces);
			shaderMulLighting.setFloat("pointLights[22].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[22].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//23 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[23].position", glm::value_ptr((glm::vec3(-6.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[23].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[23].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[23].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[23].constant", luces2);
			shaderMulLighting.setFloat("pointLights[23].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[23].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//24Verde
			shaderMulLighting.setVectorFloat3("pointLights[24].position", glm::value_ptr((glm::vec3(-5.6, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[24].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[24].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[24].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[24].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[24].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[24].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//25 Roja
			shaderMulLighting.setVectorFloat3("pointLights[25].position", glm::value_ptr((glm::vec3(-5.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[25].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[25].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[25].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[25].constant", luces2);
			shaderMulLighting.setFloat("pointLights[25].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[25].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//26 Azul
			shaderMulLighting.setVectorFloat3("pointLights[26].position", glm::value_ptr((glm::vec3(-4.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[26].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[26].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[26].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[26].constant", luces);
			shaderMulLighting.setFloat("pointLights[26].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[26].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//27 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[27].position", glm::value_ptr((glm::vec3(-3.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[27].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[27].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[27].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[27].constant", luces2);
			shaderMulLighting.setFloat("pointLights[27].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[27].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//28Verde
			shaderMulLighting.setVectorFloat3("pointLights[28].position", glm::value_ptr((glm::vec3(-3.2, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[28].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[28].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[28].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[28].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[28].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[28].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//29 Roja
			shaderMulLighting.setVectorFloat3("pointLights[29].position", glm::value_ptr((glm::vec3(-2.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[29].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[29].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[29].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[29].constant", luces2);
			shaderMulLighting.setFloat("pointLights[29].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[29].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//32Azul
			shaderMulLighting.setVectorFloat3("pointLights[30].position", glm::value_ptr((glm::vec3(-2.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[30].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[30].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[30].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[30].constant", luces);
			shaderMulLighting.setFloat("pointLights[30].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[30].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//33 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[31].position", glm::value_ptr((glm::vec3(-1.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[31].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[31].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[31].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[31].constant", luces2);
			shaderMulLighting.setFloat("pointLights[31].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[31].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//34Verde
			shaderMulLighting.setVectorFloat3("pointLights[32].position", glm::value_ptr((glm::vec3(-0.8, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[32].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[32].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[32].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[32].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[32].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[32].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//35 Roja
			shaderMulLighting.setVectorFloat3("pointLights[33].position", glm::value_ptr((glm::vec3(-0.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[33].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[33].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[33].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[33].constant", luces2);
			shaderMulLighting.setFloat("pointLights[33].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[33].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//36 Azul
			shaderMulLighting.setVectorFloat3("pointLights[34].position", glm::value_ptr((glm::vec3(0.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[34].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[34].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[34].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[34].constant", luces);
			shaderMulLighting.setFloat("pointLights[34].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[34].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//37 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[35].position", glm::value_ptr((glm::vec3(1.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[35].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[35].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[35].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[35].constant", luces2);
			shaderMulLighting.setFloat("pointLights[35].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[35].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//38Verde
			shaderMulLighting.setVectorFloat3("pointLights[36].position", glm::value_ptr((glm::vec3(1.6, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[36].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[36].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[36].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[36].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[36].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[36].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//39 Roja
			shaderMulLighting.setVectorFloat3("pointLights[37].position", glm::value_ptr((glm::vec3(2.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[37].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[37].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[37].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[37].constant", luces2);
			shaderMulLighting.setFloat("pointLights[37].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[37].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//40 Azul
			shaderMulLighting.setVectorFloat3("pointLights[38].position", glm::value_ptr((glm::vec3(2.80, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[38].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[38].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[38].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[38].constant", luces);
			shaderMulLighting.setFloat("pointLights[38].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[38].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//41 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[39].position", glm::value_ptr((glm::vec3(3.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[39].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[39].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[39].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[39].constant", luces2);
			shaderMulLighting.setFloat("pointLights[39].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[39].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//40Verde
			shaderMulLighting.setVectorFloat3("pointLights[40].position", glm::value_ptr((glm::vec3(4.0, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[40].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[40].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[40].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[40].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[40].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[40].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//41 Roja
			shaderMulLighting.setVectorFloat3("pointLights[41].position", glm::value_ptr((glm::vec3(4.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[41].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[41].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[41].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[41].constant", luces2);
			shaderMulLighting.setFloat("pointLights[41].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[41].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//42 Azul
			shaderMulLighting.setVectorFloat3("pointLights[42].position", glm::value_ptr((glm::vec3(5.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[42].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[42].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[42].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[42].constant", luces);
			shaderMulLighting.setFloat("pointLights[42].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[42].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//43 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[43].position", glm::value_ptr((glm::vec3(5.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[43].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[43].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[43].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[43].constant", luces2);
			shaderMulLighting.setFloat("pointLights[43].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[43].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//>>>>>>>>>>>>>>>>>>>>>>>>>
			//44Verde
			shaderMulLighting.setVectorFloat3("pointLights[44].position", glm::value_ptr((glm::vec3(6.4, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[44].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[44].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[44].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[44].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[44].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[44].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//45 Roja
			shaderMulLighting.setVectorFloat3("pointLights[45].position", glm::value_ptr((glm::vec3(7.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[45].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[45].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[45].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[45].constant", luces2);
			shaderMulLighting.setFloat("pointLights[45].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[45].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//46 Azul
			shaderMulLighting.setVectorFloat3("pointLights[46].position", glm::value_ptr((glm::vec3(7.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[46].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[46].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[46].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[46].constant", luces);
			shaderMulLighting.setFloat("pointLights[46].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[46].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//47 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[47].position", glm::value_ptr((glm::vec3(8.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[47].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[47].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[47].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[47].constant", luces2);
			shaderMulLighting.setFloat("pointLights[47].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[47].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//48Verde
			shaderMulLighting.setVectorFloat3("pointLights[48].position", glm::value_ptr((glm::vec3(8.8, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[48].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[48].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[48].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[48].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[48].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[48].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//49 Roja
			shaderMulLighting.setVectorFloat3("pointLights[49].position", glm::value_ptr((glm::vec3(9.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[49].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[49].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[49].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[49].constant", luces2);
			shaderMulLighting.setFloat("pointLights[49].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[49].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//50 Azul
			shaderMulLighting.setVectorFloat3("pointLights[50].position", glm::value_ptr((glm::vec3(10.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[50].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[50].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[50].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[50].constant", luces);
			shaderMulLighting.setFloat("pointLights[50].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[50].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//51 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[51].position", glm::value_ptr((glm::vec3(10.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[51].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[51].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[51].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[51].constant", luces2);
			shaderMulLighting.setFloat("pointLights[51].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[51].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//52Verde
			shaderMulLighting.setVectorFloat3("pointLights[52].position", glm::value_ptr((glm::vec3(11.2, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[52].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[52].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[52].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[52].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[52].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[52].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//53 Roja
			shaderMulLighting.setVectorFloat3("pointLights[53].position", glm::value_ptr((glm::vec3(11.80, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[53].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[53].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[53].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[53].constant", luces2);
			shaderMulLighting.setFloat("pointLights[53].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[53].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//54 Azul
			shaderMulLighting.setVectorFloat3("pointLights[54].position", glm::value_ptr((glm::vec3(12.40, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[54].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[54].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[54].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[54].constant", luces);
			shaderMulLighting.setFloat("pointLights[54].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[54].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//55 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[55].position", glm::value_ptr((glm::vec3(13.00, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[55].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[55].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[55].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[55].constant", luces2);
			shaderMulLighting.setFloat("pointLights[55].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[55].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//56
			shaderMulLighting.setVectorFloat3("pointLights[56].position", glm::value_ptr((glm::vec3(13.6, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[56].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[56].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[56].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[56].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[56].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[56].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//57 Roja
			shaderMulLighting.setVectorFloat3("pointLights[57].position", glm::value_ptr((glm::vec3(14.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[57].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[57].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[57].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[57].constant", luces2);
			shaderMulLighting.setFloat("pointLights[57].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[57].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//58 Azul
			shaderMulLighting.setVectorFloat3("pointLights[58].position", glm::value_ptr((glm::vec3(14.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[58].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[58].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[58].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[58].constant", luces);
			shaderMulLighting.setFloat("pointLights[58].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[58].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//59 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[59].position", glm::value_ptr((glm::vec3(15.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[59].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[59].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[59].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[59].constant", luces2);
			shaderMulLighting.setFloat("pointLights[59].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[59].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//60Verde
			shaderMulLighting.setVectorFloat3("pointLights[60].position", glm::value_ptr((glm::vec3(16.0, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[60].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[60].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[60].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[60].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[60].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[60].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//61 Roja
			shaderMulLighting.setVectorFloat3("pointLights[61].position", glm::value_ptr((glm::vec3(16.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[61].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[61].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[61].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[61].constant", luces2);
			shaderMulLighting.setFloat("pointLights[61].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[61].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//62 Azul
			shaderMulLighting.setVectorFloat3("pointLights[62].position", glm::value_ptr((glm::vec3(17.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[62].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[62].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[62].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[62].constant", luces);
			shaderMulLighting.setFloat("pointLights[62].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[62].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//63 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[63].position", glm::value_ptr((glm::vec3(17.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[63].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[63].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[63].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[63].constant", luces2);
			shaderMulLighting.setFloat("pointLights[63].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[63].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			////////////////////////////_______________________

			//64Verde
			shaderMulLighting.setVectorFloat3("pointLights[64].position", glm::value_ptr((glm::vec3(18.4, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[64].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[64].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[64].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[64].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[64].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[64].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//65 Roja
			shaderMulLighting.setVectorFloat3("pointLights[65].position", glm::value_ptr((glm::vec3(19.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[65].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[65].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[65].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[65].constant", luces2);
			shaderMulLighting.setFloat("pointLights[65].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[65].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//66 Azul
			shaderMulLighting.setVectorFloat3("pointLights[66].position", glm::value_ptr((glm::vec3(19.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[66].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[66].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[66].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[66].constant", luces);
			shaderMulLighting.setFloat("pointLights[66].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[66].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//67 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[67].position", glm::value_ptr((glm::vec3(20.20, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[67].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[67].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[67].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[67].constant", luces2);
			shaderMulLighting.setFloat("pointLights[67].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[67].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//68Verde
			shaderMulLighting.setVectorFloat3("pointLights[68].position", glm::value_ptr((glm::vec3(20.80, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[68].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[68].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[68].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[68].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[68].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[68].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//69 Roja
			shaderMulLighting.setVectorFloat3("pointLights[69].position", glm::value_ptr((glm::vec3(21.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[69].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[69].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[69].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[69].constant", luces2);
			shaderMulLighting.setFloat("pointLights[69].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[69].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//70 Azul
			shaderMulLighting.setVectorFloat3("pointLights[70].position", glm::value_ptr((glm::vec3(22.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[70].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[70].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[70].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[70].constant", luces);
			shaderMulLighting.setFloat("pointLights[70].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[70].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//71 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[71].position", glm::value_ptr((glm::vec3(22.60, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[71].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[71].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[71].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[71].constant", luces2);
			shaderMulLighting.setFloat("pointLights[71].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[71].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//72.00000Verde
			shaderMulLighting.setVectorFloat3("pointLights[72].position", glm::value_ptr((glm::vec3(23.2, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[72].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[72].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[72].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[72].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[72].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[72].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//73 Roja
			shaderMulLighting.setVectorFloat3("pointLights[73].position", glm::value_ptr((glm::vec3(23.80, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[73].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[73].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[73].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[73].constant", luces2);
			shaderMulLighting.setFloat("pointLights[73].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[73].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//74 Azul
			shaderMulLighting.setVectorFloat3("pointLights[74].position", glm::value_ptr((glm::vec3(24.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[74].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[74].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[74].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[74].constant", luces);
			shaderMulLighting.setFloat("pointLights[74].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[74].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//75 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[75].position", glm::value_ptr((glm::vec3(25.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[75].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[75].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[75].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[75].constant", luces2);
			shaderMulLighting.setFloat("pointLights[75].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[75].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//76Verde
			shaderMulLighting.setVectorFloat3("pointLights[76].position", glm::value_ptr((glm::vec3(25.6, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[76].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[76].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[76].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[76].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[76].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[76].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//77 Roja
			shaderMulLighting.setVectorFloat3("pointLights[77].position", glm::value_ptr((glm::vec3(26.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[77].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[77].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[77].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[77].constant", luces2);
			shaderMulLighting.setFloat("pointLights[77].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[77].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//78
			shaderMulLighting.setVectorFloat3("pointLights[78].position", glm::value_ptr((glm::vec3(26.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[78].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[78].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[78].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[78].constant", luces);
			shaderMulLighting.setFloat("pointLights[78].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[78].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//79 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[79].position", glm::value_ptr((glm::vec3(27.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[79].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[79].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[79].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[79].constant", luces2);
			shaderMulLighting.setFloat("pointLights[79].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[79].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//80
			shaderMulLighting.setVectorFloat3("pointLights[80].position", glm::value_ptr((glm::vec3(28.0, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[80].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[80].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[80].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[80].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[80].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[80].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//81 Roja
			shaderMulLighting.setVectorFloat3("pointLights[81].position", glm::value_ptr((glm::vec3(28.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[81].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[81].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[81].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[81].constant", luces2);
			shaderMulLighting.setFloat("pointLights[81].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[81].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//82 Azul
			shaderMulLighting.setVectorFloat3("pointLights[82].position", glm::value_ptr((glm::vec3(29.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[82].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[82].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[82].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[82].constant", luces);
			shaderMulLighting.setFloat("pointLights[82].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[82].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//83 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[83].position", glm::value_ptr((glm::vec3(29.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[83].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[83].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[83].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[83].constant", luces2);
			shaderMulLighting.setFloat("pointLights[83].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[83].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//84
			shaderMulLighting.setVectorFloat3("pointLights[84].position", glm::value_ptr((glm::vec3(30.4, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[84].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[84].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[84].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[84].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[84].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[84].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//85 Roja
			shaderMulLighting.setVectorFloat3("pointLights[85].position", glm::value_ptr((glm::vec3(31.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[85].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[85].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[85].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[85].constant", luces2);
			shaderMulLighting.setFloat("pointLights[85].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[85].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//86 Azul
			shaderMulLighting.setVectorFloat3("pointLights[86].position", glm::value_ptr((glm::vec3(31.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[86].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[86].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[86].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[86].constant", luces);
			shaderMulLighting.setFloat("pointLights[86].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[86].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//87 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[87].position", glm::value_ptr((glm::vec3(32.20, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[87].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[87].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[87].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[87].constant", luces2);
			shaderMulLighting.setFloat("pointLights[87].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[87].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//////////////////7--------------------->>>>>>>>>>>>>>>inicio nuevi
			//88
			shaderMulLighting.setVectorFloat3("pointLights[88].position", glm::value_ptr((glm::vec3(32.8, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[88].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[88].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[88].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[88].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[88].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[88].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//89 Roja
			shaderMulLighting.setVectorFloat3("pointLights[89].position", glm::value_ptr((glm::vec3(33.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[89].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[89].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[89].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[89].constant", luces2);
			shaderMulLighting.setFloat("pointLights[89].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[89].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//90 Azul
			shaderMulLighting.setVectorFloat3("pointLights[90].position", glm::value_ptr((glm::vec3(34.0, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[90].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[90].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[90].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[90].constant", luces);
			shaderMulLighting.setFloat("pointLights[90].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[90].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//91 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[91].position", glm::value_ptr((glm::vec3(34.60, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[91].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[91].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[91].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[91].constant", luces2);
			shaderMulLighting.setFloat("pointLights[91].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[91].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//92
			shaderMulLighting.setVectorFloat3("pointLights[92].position", glm::value_ptr((glm::vec3(35.2, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[92].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[92].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[92].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[92].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[92].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[92].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//93 Roja
			shaderMulLighting.setVectorFloat3("pointLights[93].position", glm::value_ptr((glm::vec3(35.80, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[93].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[93].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[93].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[93].constant", luces2);
			shaderMulLighting.setFloat("pointLights[93].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[93].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//94 Azul
			shaderMulLighting.setVectorFloat3("pointLights[94].position", glm::value_ptr((glm::vec3(36.4, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[94].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[94].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[94].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[94].constant", luces);
			shaderMulLighting.setFloat("pointLights[94].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[94].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//95 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[95].position", glm::value_ptr((glm::vec3(37.00, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[95].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[95].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[95].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[95].constant", luces2);
			shaderMulLighting.setFloat("pointLights[95].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[95].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//96
			shaderMulLighting.setVectorFloat3("pointLights[96].position", glm::value_ptr((glm::vec3(37.6, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[96].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[96].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[96].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[96].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[96].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[96].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//97 Roja
			shaderMulLighting.setVectorFloat3("pointLights[97].position", glm::value_ptr((glm::vec3(38.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[97].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[97].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[97].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[97].constant", luces2);
			shaderMulLighting.setFloat("pointLights[97].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[97].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//98 Azul
			shaderMulLighting.setVectorFloat3("pointLights[98].position", glm::value_ptr((glm::vec3(38.8, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[98].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[98].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[98].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[98].constant", luces);
			shaderMulLighting.setFloat("pointLights[98].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[98].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			// Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[99].position", glm::value_ptr((glm::vec3(39.40, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[99].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[99].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[99].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[99].constant", luces2);
			shaderMulLighting.setFloat("pointLights[99].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[99].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

			//100
			shaderMulLighting.setVectorFloat3("pointLights[100].position", glm::value_ptr((glm::vec3(40.0, 15.1, -45.2))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[100].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[100].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[100].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[100].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[100].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[100].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//101 Roja
			shaderMulLighting.setVectorFloat3("pointLights[101].position", glm::value_ptr((glm::vec3(40.6, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[101].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[101].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[101].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[101].constant", luces2);
			shaderMulLighting.setFloat("pointLights[101].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[101].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//102 Azul
			shaderMulLighting.setVectorFloat3("pointLights[102].position", glm::value_ptr((glm::vec3(40.2, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[102].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[102].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.01)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[102].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[102].constant", luces);
			shaderMulLighting.setFloat("pointLights[102].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[102].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//103 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[103].position", glm::value_ptr((glm::vec3(41.80, 15.1, -45.2))));
			shaderMulLighting.setVectorFloat3("pointLights[103].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[103].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[103].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[103].constant", luces2);
			shaderMulLighting.setFloat("pointLights[103].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[103].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;


			/*Luces en medio 1*/
			/*Luces Brandal Arriba*/



		}
		//Aqui

		/*Esto es  para colocar las esferas de las luces*/
		/*Luces de Navidad */

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-14.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		///::_________
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-11.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();
		//_---------
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		///Ya con orden
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-7.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-4.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-1.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(0.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(3.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(6.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(9.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(12.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(15.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(18.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(21.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(24.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		/////////////////////

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(27.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(30.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(33.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(36.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(39.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		///////////
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(42.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.0, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.6, 15, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.2, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.8, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(45.4, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		/*Fin  Luces*/

		/*Luces piso Abajo*/

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-14.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		///::_________
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-11.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();
		//_---------
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-7.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-4.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-1.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(0.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(3.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(6.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(9.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(12.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(15.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(18.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(21.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(24.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		/////////////////////

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(27.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(30.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(33.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(36.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(39.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		///////////
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(42.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.0, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.6, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.2, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.8, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(45.4, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();
		/*Fin  Luces*/

		///luces 3

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-14.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		///::_________
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-11.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();
		//_---------
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-7.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-7.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-4.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-1.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(0.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(3.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(6.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(9.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(12.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(15.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(18.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(21.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(24.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		/////////////////////

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(27.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(30.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(33.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(36.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(39.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		///////////
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(42.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.0, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.6, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.2, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.8, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(45.4, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		/*Fin  Luces*/

		////luces4

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-14.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-13.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-12.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		///::_________
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-11.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-10.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();
		//_---------
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-9.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-7.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-8.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-7.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-6.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-5.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-4.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-3.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-2.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-1.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-0.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(0.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(1.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(2.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(3.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(4.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(5.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(6.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(7.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(8.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(9.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(10.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(11.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(12.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(13.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(14.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(15.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(16.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(17.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(18.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(19.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(20.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(21.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(22.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(23.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(24.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		/////////////////////

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(25.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(26.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(27.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(28.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(29.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(30.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(31.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(32.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(33.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(34.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(35.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(36.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(37.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(38.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(39.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		///////////
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(40.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(41.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(42.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.0, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(43.6, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.2, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(44.8, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(45.4, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		/*Fin  Luces*/

		//Inician luces laterales 1
		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -44.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -43.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -43.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -42.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -42.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -41.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -40.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -40.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -39.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -39.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -38.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -37.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -37.20));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -36.60));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -36.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -35.4));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -34.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -34.20));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -33.60));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -33.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -32.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -31.80));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -31.20));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -30.60));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -29.40));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		///
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -28.80));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -28.20));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -27.60));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15, -27.00));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Inician luces laterales 2
		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -44.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -43.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -43.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -42.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -42.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -41.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -40.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -40.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -39.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -39.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -38.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -37.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -37.20));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -36.60));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -36.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -35.4));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -34.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -34.20));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -33.60));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -33.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -32.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -31.80));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -31.20));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -30.60));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -29.40));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		///
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -28.80));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -28.20));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -27.60));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces2, -27.00));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Inician luces laterales 3
			///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -44.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -43.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -43.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -42.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -42.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -41.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -40.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -40.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -39.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -39.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -38.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -37.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -37.20));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -36.60));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -36.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -35.4));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -34.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -34.20));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -33.60));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -33.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -32.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -31.80));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -31.20));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -30.60));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -29.40));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		///
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -28.80));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -28.20));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -27.60));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces3, -27.00));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Inician luces laterales 4
		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -45.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -44.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -43.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -43.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		//Morada
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -42.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -42.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -41.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -40.8));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -40.2));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -39.6));
		sphereLamp.setColor(glm::vec4(0.34, 0.13, 0.39, 1.0));
		sphereLamp.render();

		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -39.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -38.4));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -37.8));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -37.20));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -36.60));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -36.0));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -35.4));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -34.8));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -34.20));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -33.60));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -33.0));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -32.4));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -31.80));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -31.20));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -30.60));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -29.40));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();

		///
		//Amarillo 
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -28.80));
		sphereLamp.setColor(glm::vec4(0.8, 0.8, 0.0, 1.0));
		sphereLamp.render();

		///Verde
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -28.20));
		sphereLamp.setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -27.60));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Azul
		sphereLamp.setScale(glm::vec3(0.2, 0.2, 0.3));
		sphereLamp.setPosition(glm::vec3(-15.5, 15 - aumentoLuces, -27.00));
		sphereLamp.setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
		sphereLamp.render();


		glm::mat4 lightModelmatrix = glm::rotate(glm::mat4(1.0f), angle,
			glm::vec3(1.0f, 0.0f, 0.0f));
		lightModelmatrix = glm::translate(lightModelmatrix,
			glm::vec3(0.0f, 0.0f, -ratio));

		// Posicion luz para objetos con color
		shaderColorLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));

		// Posicion luz para objetos con textura
		shaderTextureLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));

		// Posicion luz para objetos con materiales
		shaderMaterialLighting.setVectorFloat3("light.position",
			glm::value_ptr(
				glm::vec4(
					lightModelmatrix
					* glm::vec4(0.0, 0.0, 0.0, 1.0))));
		sphereLamp.render(lightModelmatrix);

		/*----------------------------------------------Todo Bien Hasta Aqui --------------------------------------------------*/

		/*------------------------------------------------------------------Inicio de primera casa ---------------------------------------------------------------------------*/

		/*Estructura de la casa*/
		/// PARED ATRAS ----------------------------Dos pisos completa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(15.0, 0.0, 36.5));
		box.setScale(glm::vec3(60.0, 30.0, 2.0));
		box.render();

		//Piso
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box8.setPosition(glm::vec3(15.0, -15.0, 0.0));
		box8.setScale(glm::vec3(60.0, 2.0, 75.0));
		box8.render();

		//aTecho
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box8.setPosition(glm::vec3(15.0, 15.0, 0.0));
		box8.setScale(glm::vec3(61.0, 2.0, 90.0));
		box8.render();

		//Pared lateral 1 Derecha AbajoD
		box9.setPosition(glm::vec3(-15.0, -7.5, 0.0));
		box9.setScale(glm::vec3(1.0, 17.0, 75.0));
		box9.render();

		//Pared lateral 1 Derecha Arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(-15.0, 8.0, 5.00));
		box9.setScale(glm::vec3(1.0, 16.0, 65.0));
		box9.render();

		//Pared lateral 2 Izquierda
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box10.setPosition(glm::vec3(45.0, 0.0, 0.0));
		box10.setScale(glm::vec3(1.0, 32.0, 75.0));
		box10.render();


		//Pared medio por escaleras
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(24.75, 7.5, -18.00));
		box9.setScale(glm::vec3(0.5, 13.0, 39.0));
		box9.render();

		//Piso intermedio
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box8.setPosition(glm::vec3(5.0, 0.0, 0.0));
		box8.setScale(glm::vec3(40.0, 2.0, 90.0));
		box8.render();

		//Pasto -piso
		glBindTexture(GL_TEXTURE_2D, textureID14);
		box8.setPosition(glm::vec3(15.0, -14.4, 0.0));
		box8.setScale(glm::vec3(300.0, 0.5, 200.0));
		box8.render();

		/*Fin de la Estructura de la casa*/


		/* ------------ Escaleras --------------------*/

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(26.0, -0.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(28.0, -2.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(30.0, -4.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(32.0, -6.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(34.0, -8.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(36.0, -10.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(38.0, -12.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();


		/* ------------ Fin de Escaleras --------------------*/

		/* ----------------- Barandal -----------------------*/
		/*Cadena de luces1*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(15.0, 15.04, -45.04));
		box.setScale(glm::vec3(60.0, 0.050, 0.0050));
		box.render();

		/*Cadena de luces2*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(15.0, 15.04 - aumentoLuces, -45.04));
		box.setScale(glm::vec3(60.0, 0.050, 0.0050));
		box.render();

		/*Cadena de luces3*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(15.0, 15.04 - aumentoLuces2, -45.04));
		box.setScale(glm::vec3(60.0, 0.050, 0.0050));
		box.render();

		/*Cadena de luces4*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(15.0, 15.04 - aumentoLuces3, -45.04));
		box.setScale(glm::vec3(60.0, 0.050, 0.0050));
		box.render();

		/*Cadena de luces lateral 1*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(-15.50, 15.04, -36.00));
		box.setScale(glm::vec3(0.0050, 0.050, 18.5));
		box.render();

		/*Cadena de luces lateral 1*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(-15.50, 15.04 - aumentoLuces, -36.00));
		box.setScale(glm::vec3(0.0050, 0.050, 18.5));
		box.render();

		/*Cadena de luces lateral 1*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(-15.50, 15.04 - aumentoLuces2, -36.00));
		box.setScale(glm::vec3(0.0050, 0.050, 18.5));
		box.render();
		/*Cadena de luces lateral 1*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(-15.50, 15.04 - aumentoLuces3, -36.00));
		box.setScale(glm::vec3(0.0050, 0.050, 18.5));
		box.render();


		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(-15.0, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Murito 1
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-5.0, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();

		//Murito 2
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-15.0, 3.5, -36.250));
		box.setScale(glm::vec3(1.0, 5.0, 17.5));
		box.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(-15.0, 6.0, -28.0));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(5.0, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Murito 3
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(15.0, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();



		/*------------ Fin Barandal --------------------------*/

		/* ----------------- Ventana Superior con puerta DERECHA --------------------*/


		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(-8.0, 9.0, -27.0));
		box.setScale(glm::vec3(11, 6.0, 1.0));
		box.render();

		//Murito arriba  izquierda y derecha
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(4.5, 13.0, -27.0));
		box.setScale(glm::vec3(38.0, 2.0, 1.0));
		box.render();

		//Murito 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.5, 3.0, -27.0));
		box.setScale(glm::vec3(14.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-1.5, 9.0, -27.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-14.0, 9.0, -27.0));
		box.setScale(glm::vec3(1.0, 6.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(2.0, 6.5, -27.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Fin de Ventana Superior con puerta ---------------------*/


		/* ---------- Ventana Superior con puerta izquierda   ---------------------*/

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(18.25, 9.0, -27.0));
		box.setScale(glm::vec3(10.5, 6.0, 1.0));
		box.render();
		//Murito 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(18.0, 3.0, -27.0));
		box.setScale(glm::vec3(14.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(12.0, 9.0, -27.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(24.0, 10.0, -27.0));
		box.setScale(glm::vec3(1.0, 8.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(8.25, 6.5, -27.0));
		box.setScale(glm::vec3(5.5, 11.0, 1.0));
		box.render();

		/* ---------- Fin de Ventana Superior con puerta izquierda ---------------------*/

		// Division de Cuartos Arriba 

		//Pared lateral superior que divide cuartos 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(5.0, 7.0, -13.5));
		box9.setScale(glm::vec3(1.0, 15.0, 28.0)); //60
		box9.render();

		/* ---------- Cuarto Derecho Entrada ---------------------*/

		//Murito derecheco de frente
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.5, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Murito arriba  izquierda y derecha dentro casa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(4.5, 13.0, 1.0));
		box.setScale(glm::vec3(40.0, 2.0, 1.0));
		box.render();

		//mURO 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(5.0, 6.0, 1.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(2.0, 6.5, 1.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Fin Cuarto Derecho Entrada ---------------------*/


		//Murito izuierdo de frente
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.5, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Puerta --
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(8.00, 6.5, 1.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		//Murito cuarto pelis
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(38.0, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Puerta -- pelis
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(28.00, 6.5, 1.0));
		box.setScale(glm::vec3(6.0, 11.0, 1.0));
		box.render();

		//Murito arriba  PELIS dentro casa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(35, 13.0, 1.0));
		box.setScale(glm::vec3(20.0, 2.0, 1.0));
		box.render();

		/* ---------- Cuarto izquierdo Entrada ---------------------*/

		/*----------------------Baño ------------------------------*/

		//Pared frente de escaleras banio
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(5.0, 7.0, 25.25));
		box9.setScale(glm::vec3(1.0, 15.0, 20.5));
		box9.render();

		//Murito Baño entrada
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.5, 6.0, 15.25));
		box.setScale(glm::vec3(14.0, 12.00, 0.5));
		box.render();

		//Murito arriba  izquierda y derecha dentro banio
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-5.0, 13.0, 15.25));
		box.setScale(glm::vec3(19.0, 2.0, 0.5));
		box.render();

		//Forro de arriba barrita
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-5.0, 13.0, 15.55));
		box.setScale(glm::vec3(19.0, 2.00, 0.025));
		box.render();

		//Puerta BANIO
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(2.00, 6.5, 15.25));
		box.setScale(glm::vec3(5.0, 11.0, 0.5));
		box.render();

		//Cristal baño
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-8.5, 6.0, 30.250));
		box.setScale(glm::vec3(12.20, 10.00, 0.2));
		box.render();
		/*
		//cristal baño ancho chico largo alto Muro
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-2.5, 4.0, 32.90));
		box.setScale(glm::vec3(0.20, 6.00, 5.20));
		box.render();

		*/


		//cristal baño ancho chico largo alto cristal
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-2.5, 6.0, 32.90));
		box.setScale(glm::vec3(0.20, 10.00, 5.20));
		box.render();

		//mueble madera
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-8.5, 2.0, 19.00));
		box.setScale(glm::vec3(12.20, 6.00, 0.2));
		box.render();

		//mueble madera chico
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-2.5, 2.0, 17.20));
		box.setScale(glm::vec3(0.20, 6.00, 3.5));
		box.render();

		//mueble madera tapa
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-8.5, 5.1, 17.225));
		box.setScale(glm::vec3(12.20, 0.20, 3.75));
		box.render();

		//EspejoNO madera
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-8.5, 8.7, 15.55));
		box.setScale(glm::vec3(12.20, 6.00, 0.17));
		box.render();

		//pared atras espejo forro
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-7.5, 6.0, 15.55));
		box.setScale(glm::vec3(14.0, 12.00, 0.025));
		box.render();
		//pared izquierda entrada forro
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(4.45, 7.5, 25.55));
		box.setScale(glm::vec3(00.050, 13.00, 020.0));
		box.render();
		//pared derecha entrada forro
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-14.5, 7.5, 25.55));
		box.setScale(glm::vec3(00.050, 13.00, 20.0));
		box.render();

		//pared derecha entrada forro banio  pared madera
		glBindTexture(GL_TEXTURE_2D, textureID62);
		box.setPosition(glm::vec3(-14.4, 7.5, 24.50));
		box.setScale(glm::vec3(00.050, 13.00, 8.0));
		box.render();


		//pared REGADER
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box.setPosition(glm::vec3(-5.0, 7.5, 35.50));
		box.setScale(glm::vec3(19.0, 13.00, 0.025));
		box.render();

		//Espejo
		glBindTexture(GL_TEXTURE_2D, textureID64);
		box.setPosition(glm::vec3(-8.35, 8.7, 15.650));
		box.setScale(glm::vec3(8.20, 6.00, 0.10));
		box.render();

		//Tapitas1
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-3.3, 7.0, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		//Tapitas2
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-3.3, 8.50, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		//Tapitas3
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-3.3, 10.0, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();

		//Tapitas4
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-13.5, 7.0, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-13.5, 8.5, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-13.5, 10, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();

		//Piso Banio regadera
		glBindTexture(GL_TEXTURE_2D, textureID61);
		box.setPosition(glm::vec3(-8.5, 1.0, 33.0));
		box.setScale(glm::vec3(12.0, 0.20, 5.50));
		box.render();

		/*---------------------- Fin Baño -----------------------*/

		/*----------------Barandal sala pelis--------------------*/

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(45.0, 6.0, -38.0));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(25.0, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(45.0, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Murito 1
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(35.0, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(45.0, 3.5, -41.25));
		box.setScale(glm::vec3(1.0, 5.0, 7.0));
		box.render();

		/*----------------Fin Barandal sala  pelis--------------------*/

		/*----------------Ventana sala pelis--------------------*/

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(32.5, 9.0, -37.0));
		box.setScale(glm::vec3(11, 6.0, 1.0));
		box.render();

		//Murito 2 enfrente del brandal
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(32.5, 3.0, -37.0));
		box.setScale(glm::vec3(15.0, 6.0, 1.0));
		box.render();

		//Murito 2 enfrente del brandal arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(32.5, 13.0, -37.0));
		box.setScale(glm::vec3(15.0, 2.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(26.00, 9.0, -37.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(39.00, 9.0, -37.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO Arriba de puerta
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(42.25, 13.0, -37.0));
		box.setScale(glm::vec3(4.5, 2.0, 1.0));
		box.render();

		//Puerta PELIS
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(42.25, 6.5, -37.0));
		box.setScale(glm::vec3(4.5, 11.0, 1.0));
		box.render();

		/*---------------- Fin Ventana sala pelis--------------------*/

		/*--------------------Sala de Pelis--------------------- */

		//Piso intermedio pelis
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box8.setPosition(glm::vec3(35.0, 0.0, -15.0));
		box8.setScale(glm::vec3(21.0, 2.0, 60.0));
		box8.render();

		//Murito 2 enfrente de las escaleras
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(34.75, 3.5, 14.75));
		box.setScale(glm::vec3(19.50, 5.0, 0.5));
		box.render();

		//Barandal por Escaleras
		//Pared frente de escaleras banio
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box9.setPosition(glm::vec3(24.75, 3.5, 22.5));
		box9.setScale(glm::vec3(0.5, 5.0, 16.0));
		box9.render();

		/*------------------Fin sala Pelis----------------------*/

		//// -------------  Frente  ------------------------- 

		//Muro ABAJO IZQUIERDA Funciona como pared del baño
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.0, -8.5, -37.0));
		box.setScale(glm::vec3(14, 15.0, 1.0));
		box.render();

		//Murito CUADRITO 2 ABAJO Derecha
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.0, -11.5, -37.0));
		box.setScale(glm::vec3(13, 5.0, 1.0));
		box.render();

		//Murito CUADRITO 2 arriba de parte baja
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-2.25, -2.0, -37.0));
		box.setScale(glm::vec3(24.5, 2.0, 1.0));
		box.render();

		//cASTILLO puerta 2M
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(0.50, -9.0, -37.0));
		box.setScale(glm::vec3(2.0, 12.0, 1.0));
		box.render();


		//cASTILLO Ventana 1M
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-14.0, -9.0, -37.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();

		//Puerta p
		glBindTexture(GL_TEXTURE_2D, textureID30);
		box.setPosition(glm::vec3(5.75, -8.5, -37.0));
		box.setScale(glm::vec3(8.5, 11.0, 1.0));
		box.render();

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(-7.0, -6.0, -37.0));
		box.setScale(glm::vec3(13, 6.0, 1.0));
		box.render();

		///--------------------------------------Cocina-----------------------------------------------////
		//Murito CUADRITO 2 ABAJO IZQUIERDA
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.0, -8.5, 18.0));
		box.setScale(glm::vec3(14, 15.0, 1.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.0, -8.5, -8.0));
		box.setScale(glm::vec3(14, 15.0, 1.0));
		box.render();

		//  pared  cocina completa der
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -7.5, 14.75));
		box9.setScale(glm::vec3(1.0, 14.0, 5.5));
		box9.render();

		//  pared mitad cocina
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -11.5, 6.75));
		box9.setScale(glm::vec3(1.0, 5.0, 10.5));
		box9.render();

		//  pared mitad cocina arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -2.0, 6.75));
		box9.setScale(glm::vec3(1.0, 2.0, 10.5));
		box9.render();

		//  pared  cocina completa izq
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -7.5, 0.5));
		box9.setScale(glm::vec3(1.0, 14.0, 2.0));
		box9.render();

		////-------------------------Arriba 

		//  pared mitad cocina arriba puierta
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -2.0, -4.00));
		box9.setScale(glm::vec3(1.0, 2.0, 7.0));
		box9.render();


		//  pared mitad cocina arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -2.0, -11.50));
		box9.setScale(glm::vec3(1.0, 2.0, 6.0));
		box9.render();


		// -------------------Cochera -----------------------//
		glBindTexture(GL_TEXTURE_2D, textureID12);
		box.setPosition(glm::vec3(34.75, -9.5, -37.0));
		box.setScale(glm::vec3(19.5, 13.0, 1.0));
		box.render();
		//murito arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(34.75, -2.0, -37.0));
		box.setScale(glm::vec3(19.5, 2.0, 1.0));
		box.render();

		//------------------Piso Madera -------------------//
		//Piso Q1
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-5.0, 1.00, -13.0));
		box8.setScale(glm::vec3(20.0, 0.1, 27.0));
		box8.render();
		//Piso Q2
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(15.0, 1.00, -13.0));
		box8.setScale(glm::vec3(20.0, 0.1, 27.0));
		box8.render();
		//Piso Q3 p1
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(35.0, 1.00, -23.0));
		box8.setScale(glm::vec3(20.0, 0.1, 27.0));
		box8.render();
		//Piso Q3 p2W
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(35.0, 1.00, 2.5));
		box8.setScale(glm::vec3(20.0, 0.1, 24.0));
		box8.render();

		//Piso Fuera Banio P1
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(15.0, 1.00, 18.75));
		box8.setScale(glm::vec3(20.0, 0.1, 36.75));
		box8.render();

		//Piso Fuera Banio P2
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-5.0, 1.00, 8.00));
		box8.setScale(glm::vec3(20.0, 0.1, 14.00));
		box8.render();

		//Piso Banio
		glBindTexture(GL_TEXTURE_2D, textureID61);
		box8.setPosition(glm::vec3(-5.0, 1.00, 25.50));
		box8.setScale(glm::vec3(20.0, 0.1, 21.00));
		box8.render();

		//Piso sala
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-2.50, -14.00, -22.50));
		box8.setScale(glm::vec3(25.0, 0.1, 28.0));
		box8.render();

		//Piso sala II
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-2.50, -14.00, 5.0));
		box8.setScale(glm::vec3(25.0, 0.1, 27.0));
		box8.render();

		//Piso banio abajo
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(17.0, -14.00, -22.50));
		box8.setScale(glm::vec3(14.0, 0.1, 28.0));
		box8.render();

		//Piso cocina 
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(17.0, -14.00, 5.0));
		box8.setScale(glm::vec3(14.0, 0.1, 27.0));
		box8.render();

		//Piso atras 
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-2.50, -14.00, 27.0));
		box8.setScale(glm::vec3(25.0, 0.1, 17.0));
		box8.render();

		/*Entrada por estacionamiento*/
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -2.0, 32.750));
		box9.setScale(glm::vec3(1.0, 2.0, 6.5));
		box9.render();

		//  pared  grande
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -7.5, 24.0));
		box9.setScale(glm::vec3(1.0, 14.0, 11.0));
		box9.render();

		/* -----------------------Inician Accesorios ----------------------------------*/

		/*Comedor*/

		//___________________Cuadros  Sala
		glBindTexture(GL_TEXTURE_2D, textureID92);
		box9.setPosition(glm::vec3(-14.4, -5.4, -22.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID93);
		box9.setPosition(glm::vec3(-14.4, -4.5, -19.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID94);
		box9.setPosition(glm::vec3(-14.4, -6.2, -19.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		//___________________Cuadros  comedor

		glBindTexture(GL_TEXTURE_2D, textureID95);
		box9.setPosition(glm::vec3(-14.4, -5.4, 4.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID98);
		box9.setPosition(glm::vec3(-14.4, -5.4, 8.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID96);
		box9.setPosition(glm::vec3(-14.4, -5.4, 12.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		//___________________Cuadros  comedor frente 

		glBindTexture(GL_TEXTURE_2D, textureID97);
		box9.setPosition(glm::vec3(10.0, -4.4, 22.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		/*matel Navidad*/

		//glBindTexture(GL_TEXTURE_2D, textureID97);
		//box9.setPosition(glm::vec3(-3.95, -9.05, 9.50));
		//box9.setScale(glm::vec3(7.1, 0.02, 12.0));
		//box9.render();

		/*Rosca de Reyes*/
		glBindTexture(GL_TEXTURE_2D, textureID102);
		box9.setPosition(glm::vec3(-3.95, -9.0, 09.50));
		box9.setScale(glm::vec3(3.1, 0.4, 4.0));
		box9.render();

		/* init  Sala */

		//______________________TV Sala peli
		glBindTexture(GL_TEXTURE_2D, textureID99);
		box9.setPosition(glm::vec3(10.0, -6.0, -21.0));
		box9.setScale(glm::vec3(0.15, 4.5, 8.0));
		box9.render();
		//______________________TV Sala tv
		glBindTexture(GL_TEXTURE_2D, textureID101);
		box9.setPosition(glm::vec3(10.0, -6.0, -21.0));
		box9.setScale(glm::vec3(0.10, 4.9, 8.4));
		box9.render();

		/* Primer Cuarto */

		//_________________Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID32);
		box9.setPosition(glm::vec3(-14.5, 7.5, -13.0));
		box9.setScale(glm::vec3(0.10, 13.0, 27.0));
		box9.render();
		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-8.5, 6.0, -0.750));
		box9.setScale(glm::vec3(12.0, 10.0, 2.5));
		box9.render(0, 6);
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.render(6, 6);
		glBindTexture(GL_TEXTURE_2D, textureID31);
		box9.render(12, 6);
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.render(18, 6);
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.render(24, 6);


		//______________________TV
		glBindTexture(GL_TEXTURE_2D, textureID38);
		box9.setPosition(glm::vec3(4.5, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 3.0, 6.0));
		box9.render();

		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-14.3, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID34);
		box9.setPosition(glm::vec3(-10.0, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-10.0, 1.5, -14.0));
		box9.setScale(glm::vec3(8.3, 1.0, 7.0));
		box9.render();


		//___________________Almohada_1
		glBindTexture(GL_TEXTURE_2D, textureID32);
		cylinder3.setPosition(glm::vec3(-13.6, 4.0, -12.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_2
		glBindTexture(GL_TEXTURE_2D, textureID34);
		cylinder3.setPosition(glm::vec3(-13.6, 4.0, -14.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_3
		glBindTexture(GL_TEXTURE_2D, textureID33);
		cylinder3.setPosition(glm::vec3(-13.6, 4.0, -16.4));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID33);
		cylinder3.setPosition(glm::vec3(-13.1, 4.0, -13.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//__________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID32);
		cylinder3.setPosition(glm::vec3(-13.1, 4.0, -15.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.7, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.7, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Espejo Cuarto
		glBindTexture(GL_TEXTURE_2D, textureID39);
		box9.setPosition(glm::vec3(-14.38, 6.5, -5.50));
		box9.setScale(glm::vec3(0.1, 7.0, 3.0));
		box9.render();

		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4, 8.4, -15.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID36);
		box9.setPosition(glm::vec3(-14.4, 7.5, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID37);
		box9.setPosition(glm::vec3(-14.4, 9.2, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.5, 2.5, -22.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.5, 2.5, -26.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.5, 4.45, -24.00));
		box9.setScale(glm::vec3(2.0, 0.4, 4.20));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-14.4, 2.00, -24.00));
		box9.setScale(glm::vec3(0.1, 1.0, 4.20));
		box9.render();

		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID33);
		box9.setPosition(glm::vec3(-5.0, 1.05, -14.00));
		box9.setScale(glm::vec3(8.0, 0.05, 14.00));
		box9.render();

		/* Segundo Cuarto Cuarto De Niño */
		//_________________Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID42);
		box9.setPosition(glm::vec3(24.5, 7.5, -13.0));
		box9.setScale(glm::vec3(0.10, 13.0, 27.0));
		box9.render();

		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(23.0, 6.0, -02.750));
		box9.setScale(glm::vec3(3.0, 10.0, 6.0));
		box9.render(0, 6);
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.render(6, 6);
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.render(12, 6);
		glBindTexture(GL_TEXTURE_2D, textureID41);
		box9.render(18, 6);
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.render(24, 6);

		//______________________TV
		glBindTexture(GL_TEXTURE_2D, textureID100);
		box9.setPosition(glm::vec3(4.5 + 1.0, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 3.0, 6.0));
		box9.render();

		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-14.3 + 38.7, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID45);
		box9.setPosition(glm::vec3(-10.0 + 30.1, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-10.0 + 30, 1.5, -14.0));
		box9.setScale(glm::vec3(8.3, 1.0, 7.0));
		box9.render();

		//___________________Almohada_1
		glBindTexture(GL_TEXTURE_2D, textureID7);
		cylinder3.setPosition(glm::vec3(-10.0 + 34, 4.0, -11.6));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Almohada_2
		glBindTexture(GL_TEXTURE_2D, textureID43);
		cylinder3.setPosition(glm::vec3(-10.0 + 34, 4.0, -13.8));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_3
		glBindTexture(GL_TEXTURE_2D, textureID7);
		cylinder3.setPosition(glm::vec3(-10.0 + 34, 4.0, -16.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID43);
		cylinder3.setPosition(glm::vec3(-10.5 + 34, 4.0, -12.7));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID40);
		cylinder3.setPosition(glm::vec3(-10.5 + 34, 4.0, -14.9));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.7 + 37.4, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.7 + 37.4, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Espejo Cuarto
		glBindTexture(GL_TEXTURE_2D, textureID44);
		box9.setPosition(glm::vec3(-14.38 + 38.8, 6.5, -22.50));
		box9.setScale(glm::vec3(0.1, 7.0, 3.0));
		box9.render();

		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.5 + 30, 2.5, -01.00));
		box9.setScale(glm::vec3(0.20, 3.5, 02.5));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-15.5 + 28, 2.5, -01.00));
		box9.setScale(glm::vec3(0.20, 3.5, 02.5));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.5 + 28, 4.45, -01.00));
		box9.setScale(glm::vec3(4.20, 0.4, 2.50));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-14.4 + 28.9, 2.00, -0.00));
		box9.setScale(glm::vec3(4.20, 1.0, 0.1));
		box9.render();



		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID48);
		box9.setPosition(glm::vec3(-14.4 + 38.8, 8.4, -15.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID46);
		box9.setPosition(glm::vec3(-14.4 + 38.8, 8.4, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();



		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID43);
		cylinder3.setPosition(glm::vec3(-5.0 + 20.5, 1.05, -14.00));
		cylinder3.setScale(glm::vec3(8.0, 0.05, 14.00));
		cylinder3.render();


		/* Tercer Cuarto Cuarto */
		//_________________Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID52);
		box9.setPosition(glm::vec3(25.0, 7.5, -18.00));
		box9.setScale(glm::vec3(0.10, 13.0, 37.0));
		box9.render();

		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(38.5, 6.0, -0.750));
		box9.setScale(glm::vec3(12.0, 10.0, 2.5));
		box9.render(0, 6);
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.render(6, 6);
		glBindTexture(GL_TEXTURE_2D, textureID51);
		box9.render(12, 6);
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.render(18, 6);
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.render(24, 6);

		//______________________TV
		glBindTexture(GL_TEXTURE_2D, textureID101);
		box9.setPosition(glm::vec3(4.95 + 39.5, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 4.0, 8.0));
		box9.render();


		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-14.3 + 39.5, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID54);
		box9.setPosition(glm::vec3(-10.0 + 39.5, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-10.0 + 39.5, 1.5, -14.0));
		box9.setScale(glm::vec3(8.3, 1.0, 7.0));
		box9.render();


		//___________________Almohada
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.6 + 39.5, 4.5, -12.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_2
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.6 + 39.5, 4.5, -14.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_3
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.6 + 39.5, 4.5, -16.4));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.1 + 39.5, 4.5, -13.1));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.1 + 39.5, 4.5, -15.3));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();


		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.7 + 39.5, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.7 + 39.5, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Espejo Cuarto
		/*glBindTexture(GL_TEXTURE_2D, textureID17);
		box9.setPosition(glm::vec3(-14.38 + 39.5, 6.5, -5.50));
		box9.setScale(glm::vec3(0.1, 7.0, 3.0));
		box9.render();*/

		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID56);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 8.4, -17.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID57);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 8.4, -14.1));
		box9.setScale(glm::vec3(0.1, 3.6, 1.8));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID59);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 7.5, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID58);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 9.2, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID60);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 8.35, -9.5));
		box9.setScale(glm::vec3(0.1, 1.5, 2.5));
		box9.render();
		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.5 + 39.5, 2.5, -24.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.5 + 39.5, 2.5, -32.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.5 + 39.5, 4.45, -28.00));
		box9.setScale(glm::vec3(2.0, 0.4, 8.20));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 2.00, -28.00));
		box9.setScale(glm::vec3(0.1, 1.0, 8.20));
		box9.render();

		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID55);
		box9.setPosition(glm::vec3(-5.0 + 39.5, 1.05, -14.00));
		box9.setScale(glm::vec3(8.0, 0.05, 14.00));
		box9.render();

		//_________________________Pizarron
		glBindTexture(GL_TEXTURE_2D, textureID53);
		box9.setPosition(glm::vec3(-14.4 + 39.5, 8.4, -28.00));
		box9.setScale(glm::vec3(0.1, 6.0, 10.0));
		box9.render();

		/*---------- Cocina Muebles-------------*/

		//Refrijerador
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.5, -8.5, -5.00));
		box.setScale(glm::vec3(3.0, 11.00, 5.0));
		box9.render();


		/*---------- Cocina Muebles-------------*/

		//Refrijerador
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.5, -8.5, -5.00));
		box.setScale(glm::vec3(3.0, 11.00, 5.0));
		box.render();

		//Mueble madera  der
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.63, -11.0, 14.50));
		box.setScale(glm::vec3(3.0, 6.00, 6.0));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.63, -11.0, 10.55));
		box.setScale(glm::vec3(3.0, 6.00, 1.9));
		box.render();

		//Mueble madera izq
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.6, -11.0, 1.00));
		box.setScale(glm::vec3(3.0, 6.00, 6.0));
		box.render();

		//Estufa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.6, -11.0, 6.800));//.25
		box.setScale(glm::vec3(3.0, 6.00, 5.6));
		box.render();

		//--Arriba
		//Mueble madera  der
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.63, -2.5, 13.50));
		box.setScale(glm::vec3(3.0, 3.00, 8.9));
		box.render();

		//Mueble madera  izq
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.6, -2.5, 1.00));
		box.setScale(glm::vec3(3.0, 3.00, 6.0));
		box.render();

		//Arriba Estufa mueble
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.6, -2.25, 6.800));//.25
		box.setScale(glm::vec3(3.0, 2.50, 5.6));
		box.render();
		//Arriba Estufa grasa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.1, -3.75, 6.800));//.25
		box.setScale(glm::vec3(4.0, 0.50, 5.6));
		box.render();

		//Mueble madera  izqcosas  
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(14.5, -11.0, 16.00));
		box.setScale(glm::vec3(7.0, 6.00, 3.0));
		box.render();

		//Mueble madera izqcosas  arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(14.5, -2.5, 16.00));
		box.setScale(glm::vec3(7.0, 3.00, 3.0));
		box.render();

		//microondaas
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(16.5, -7.25, 16.750));
		box.setScale(glm::vec3(3.0, 1.50, 1.5));
		box.render();

		//mesa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(10.5, -9.00, 6.750));
		box.setScale(glm::vec3(3.5, 0.20, 10.50));
		box.render();

		/*Compu afuera de cuartos */
		//  pared separa cochera 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(24.5, -8.5, -9.5));
		box9.setScale(glm::vec3(1.0, 15.0, 56.0));
		box9.render();
		//  pared separa sala y pared cochera
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5, -8.5, -25.5));
		box9.setScale(glm::vec3(1.0, 15.0, 22.0));
		box9.render();

		//---- Entrada del coche Cochera -----//
		glBindTexture(GL_TEXTURE_2D, textureID5);
		box8.setPosition(glm::vec3(34.75, -14.00, -55.8));
		box8.setScale(glm::vec3(21.5, 0.1, 38.0));
		box8.render();
		//---- Entrada del coche Calle -----//
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(34.75, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(13.25, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-8.25, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-29.75, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-51.25, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		//izquierda
		glBindTexture(GL_TEXTURE_2D, textureID5);
		box8.setPosition(glm::vec3(-72.75, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-72.75, -14.00, -63.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-72.75, -14.00, -41.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-72.75, -14.00, -18.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-72.75, -14.00, 4.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-72.75, -14.00, 26.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-72.75, -14.00, 49.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		//izquierda Atras
		glBindTexture(GL_TEXTURE_2D, textureID5);
		box8.setPosition(glm::vec3(-72.75, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		//linea carretera atras(izq-der)
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-51.25, -14.00, 71.5));
		box8.setScale(glm::vec3(22.0, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-29.5, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-8.25, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(13.25, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(34.75, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(56.25, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(77.75, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(99.25, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(120.75, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		//esquina derecha atras
		glBindTexture(GL_TEXTURE_2D, textureID5);
		box8.setPosition(glm::vec3(142.25, -14.00, 71.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		//linea carretera atras(izq-der)
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(142.25, -14.00, 49.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(142.25, -14.00, 26.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(142.25, -14.00, 4.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(142.25, -14.00, -18.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(142.25, -14.00, -41.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(142.25, -14.00, -63.5));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		//Esquina dercha
		glBindTexture(GL_TEXTURE_2D, textureID5);
		box8.setPosition(glm::vec3(142.25, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(120.75, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(99.25, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(77.75, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(56.25, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		//Puertas Abajo 

		//Puerta oficina
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(10.5, -8.5, -11.50));
		box.setScale(glm::vec3(1.0, 11.0, 6.0));
		box.render();

		//Puerta entrada
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(10.5, -8.5, 32.5));
		box.setScale(glm::vec3(1, 11.0, 6.0));
		box.render();

		//Helipuerto
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box8.setPosition(glm::vec3(-35.00, -14.00, -20.0));
		box8.setScale(glm::vec3(25.0, 0.1, 35.0));
		box8.render();
		//HelipuertoLogo
		glBindTexture(GL_TEXTURE_2D, textureID31);
		box8.setPosition(glm::vec3(-35.00, -13.95, -20.0));
		box8.setScale(glm::vec3(25.0, 0.1, 35.0));
		box8.render();


		/*------------------------------------------------------------Fin--------------------------w---------------------------------*/

		//Perro
		glm::mat4 perro = glm::mat4(1.0);
		perro = glm::translate(perro, glm::vec3(35.0, 1.0, -42.0));
		perro = glm::scale(perro, glm::vec3(0.10, 0.10, 0.10));
		perro = glm::rotate(perro, glm::radians(360.0f), glm::vec3(1.0, 0.0, 2.0));
		modelCami.render(perro);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelMesa

		glm::mat4 Mesa = glm::mat4(1.0);
		Mesa = glm::translate(Mesa, glm::vec3(-12.0, 1.0, 8.0));
		Mesa = glm::scale(Mesa, glm::vec3(8.0, 8.0, 8.00));
		ModelMesa.render(Mesa);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);



		/*------------------------------------------------------------------Inicio de segunda casa ---------------------------------------------------------------------------*/

		/*Estructura de la casa*/
		// PARED ATRAS ----------------------------Dos pisos completa
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(04.5 + suma, 0.0, 36.5));
		box.setScale(glm::vec3(40.0, 30.0, 2.0));
		box.render();

		//Piso
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box8.setPosition(glm::vec3(04.5 + suma, -15.0, 0.0));
		box8.setScale(glm::vec3(40.0, 2.0, 75.0));
		box8.render();

		//aTecho
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box8.setPosition(glm::vec3(04.5 + suma, 15.0, 0.0));
		box8.setScale(glm::vec3(40.0, 2.0, 90.0));
		box8.render();

		//Pared lateral 1 Derecha AbajoD
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box9.setPosition(glm::vec3(-15.0 + suma, -7.5, 0.0));
		box9.setScale(glm::vec3(1.0, 17.0, 75.0));
		box9.render();

		//Pared lateral 1 Derecha Arriba
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box9.setPosition(glm::vec3(-15.0 + suma, 8.0, 5.00));
		box9.setScale(glm::vec3(1.0, 16.0, 65.0));
		box9.render();

		//Pared izquierda
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box9.setPosition(glm::vec3(24.75 + suma,0.0, -0.00));
		box9.setScale(glm::vec3(1.50, 32.0, 75.0));
		box9.render();

		//Piso intermedio
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box8.setPosition(glm::vec3(5.0 + suma, 0.0, 0.0));
		box8.setScale(glm::vec3(40.0, 2.0, 90.0));
		box8.render();
		/*Fin de la Estructura de la casa*/



		/* ------------ Escaleras --------------------*/
		
		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(26.0 + xx, -0.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box9.setPosition(glm::vec3(28.0 + xx, -2.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box9.setPosition(glm::vec3(30.0 + xx, -4.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box9.setPosition(glm::vec3(32.0 + xx, -6.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box9.setPosition(glm::vec3(34.0 + xx, -8.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box9.setPosition(glm::vec3(36.0 + xx, -10.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID71);
		box9.setPosition(glm::vec3(38.0 + xx, -12.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();
		/* ------------ Fin de Escaleras --------------------*/

		/* ----------------- Barandal -----------------------*/
		

		//Murito 1
		glBindTexture(GL_TEXTURE_2D, textureID1);
		box.setPosition(glm::vec3(-5.0 + suma, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();

		//Murito 2
		glBindTexture(GL_TEXTURE_2D, textureID1);
		box.setPosition(glm::vec3(-15.0 + suma, 3.5, -36.250));
		box.setScale(glm::vec3(1.0, 5.0, 17.5));
		box.render();

		//Murito 3
		glBindTexture(GL_TEXTURE_2D, textureID1);
		box.setPosition(glm::vec3(15.0 + suma, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();

		/*------------ Fin Barandal --------------------------*/

		/* ----------------- Ventana Superior con puerta DERECHA --------------------*/


		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID24);
		box.setPosition(glm::vec3(-8.0 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(11, 6.0, 1.0));
		box.render();

		//Murito arriba  izquierda y derecha
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(4.5 + suma, 13.0, -27.0));
		box.setScale(glm::vec3(38.0, 2.0, 1.0));
		box.render();

		//Murito 
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-7.5 + suma, 3.0, -27.0));
		box.setScale(glm::vec3(14.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-1.5 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-14.0 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(1.0, 6.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID18);
		box.setPosition(glm::vec3(2.0 + suma, 6.5, -27.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Fin de Ventana Superior con puerta ---------------------*/


		/* ---------- Ventana Superior con puerta izquierda   ---------------------*/

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID24);
		box.setPosition(glm::vec3(18.25 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(10.5, 6.0, 1.0));
		box.render();
		//Murito 
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(18.0 + suma, 3.0, -27.0));
		box.setScale(glm::vec3(14.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(12.0 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(24.0 + suma, 10.0, -27.0));
		box.setScale(glm::vec3(1.0, 8.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID18);
		box.setPosition(glm::vec3(8.25 + suma, 6.5, -27.0));
		box.setScale(glm::vec3(5.5, 11.0, 1.0));
		box.render();

		/* ---------- Fin de Ventana Superior con puerta izquierda ---------------------*/

		// Division de Cuartos Arriba 

		//Pared lateral superior que divide cuartos 
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box9.setPosition(glm::vec3(5.0 + suma, 7.0, -13.5));
		box9.setScale(glm::vec3(1.0, 15.0, 28.0)); //60
		box9.render();

		/* ---------- Cuarto Derecho Entrada ---------------------*/

		//Murito derecheco de frente
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-7.5 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Murito arriba  izquierda y derecha dentro casa
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(4.5 + suma, 13.0, 1.0));
		box.setScale(glm::vec3(40.0, 2.0, 1.0));
		box.render();

		//mURO 
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(5.0 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID18);
		box.setPosition(glm::vec3(2.0 + suma, 6.5, 1.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Fin Cuarto Derecho Entrada ---------------------*/
		//Murito izuierdo de frente
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(17.5 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Puerta 
		glBindTexture(GL_TEXTURE_2D, textureID18);
		box.setPosition(glm::vec3(8.00 + suma, 6.5, 1.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Cuarto izquierdo Entrada ---------------------*/
		/*-----------------------Decoracion de dia de muertos-------------------------------*/
		/*Arriba */

		glBindTexture(GL_TEXTURE_2D, textureID110);
		box8.setPosition(glm::vec3(15.0 + suma + 15.0 - 26.0, -2.0, -45.0));
		box8.setScale(glm::vec3(32.0, 4.0, 0.1));
		box8.render();
		/*Abajo */

		glBindTexture(GL_TEXTURE_2D, textureID110);
		box8.setPosition(glm::vec3(15.0 + suma + 15.0 - 26.0, -2.0 + 15.0, -45.0));
		box8.setScale(glm::vec3(32.0, 4.0, 0.1));
		box8.render();
		/*---------------------Fin Decoracion de dia de muertos-----------------------------*/

		/*----------------------Baño ------------------------------*/

		//Pared frente de escaleras banio
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box9.setPosition(glm::vec3(5.0 + suma, 7.0, 25.25));
		box9.setScale(glm::vec3(1.0, 15.0, 20.5));
		box9.render();

		//Murito Baño entrada
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-7.5 + suma, 6.0, 15.25));
		box.setScale(glm::vec3(14.0, 12.00, 0.5));
		box.render();

		//Murito arriba  izquierda y derecha dentro banio
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-5.0 + suma, 13.0, 15.25));
		box.setScale(glm::vec3(19.0, 2.0, 0.5));
		box.render();

		//Forro de arriba barrita
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-5.0 + suma, 13.0, 15.55));
		box.setScale(glm::vec3(19.0, 2.00, 0.025));
		box.render();

		//Puerta BANIO
		glBindTexture(GL_TEXTURE_2D, textureID18);
		box.setPosition(glm::vec3(2.00 + suma, 6.5, 15.25));
		box.setScale(glm::vec3(5.0, 11.0, 0.5));
		box.render();

		//Cristal baño
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-8.5 + suma, 6.0, 30.250));
		box.setScale(glm::vec3(12.20, 10.00, 0.2));
		box.render();

		//cristal baño ancho chico largo alto cristal
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-2.5 + suma, 6.0, 32.90));
		box.setScale(glm::vec3(0.20, 10.00, 5.20));
		box.render();

		//mueble madera
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-8.5 + suma, 2.0, 19.00));
		box.setScale(glm::vec3(12.20, 6.00, 0.2));
		box.render();

		//mueble madera chico
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-2.5 + suma, 2.0, 17.20));
		box.setScale(glm::vec3(0.20, 6.00, 3.5));
		box.render();

		//mueble madera tapa
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-8.5 + suma, 5.1, 17.225));
		box.setScale(glm::vec3(12.20, 0.20, 3.75));
		box.render();

		//EspejoNO madera
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-8.5 + suma, 8.7, 15.55));
		box.setScale(glm::vec3(12.20, 6.00, 0.17));
		box.render();

		//pared atras espejo forro
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-7.5 + suma, 6.0, 15.55));
		box.setScale(glm::vec3(14.0, 12.00, 0.025));
		box.render();
		//pared izquierda entrada forro
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(4.45 + suma, 7.5, 25.55));
		box.setScale(glm::vec3(00.050, 13.00, 020.0));
		box.render();
		//pared derecha entrada forro
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-14.5 + suma, 7.5, 25.55));
		box.setScale(glm::vec3(00.050, 13.00, 20.0));
		box.render();

		//pared derecha entrada forro banio  pared madera
		glBindTexture(GL_TEXTURE_2D, textureID62);
		box.setPosition(glm::vec3(-14.4 + suma, 7.5, 24.50));
		box.setScale(glm::vec3(00.050, 13.00, 8.0));
		box.render();


		//pared REGADER
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box.setPosition(glm::vec3(-5.0 + suma, 7.5, 35.50));
		box.setScale(glm::vec3(19.0, 13.00, 0.025));
		box.render();

		//Espejo
		glBindTexture(GL_TEXTURE_2D, textureID64);
		box.setPosition(glm::vec3(-8.35 + suma, 8.7, 15.650));
		box.setScale(glm::vec3(8.20, 6.00, 0.10));
		box.render();

		//Tapitas1
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-3.3 + suma, 7.0, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		//Tapitas2
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-3.3 + suma, 8.50, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		//Tapitas3
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-3.3 + suma, 10.0, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();

		//Tapitas4
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-13.5 + suma, 7.0, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-13.5 + suma, 8.5, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-13.5 + suma, 10, 16.0));
		box.setScale(glm::vec3(1.80, 0.20, 1.0));
		box.render();

		//Piso Banio regadera
		glBindTexture(GL_TEXTURE_2D, textureID61);
		box.setPosition(glm::vec3(-8.5 + suma, 1.0, 33.0));
		box.setScale(glm::vec3(12.0, 0.20, 5.50));
		box.render();

		/*---------------------- Fin Baño -----------------------*/
		
		//Pared frente de escaleras banio
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box9.setPosition(glm::vec3(24.75 + suma, 3.5, 22.5));
		box9.setScale(glm::vec3(0.5, 5.0, 16.0));
		box9.render();



		//// -------------  Frente  ------------------------- 

		//Muro ABAJO IZQUIERDA del frente casa 2
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(17.0 + suma, -11.5, -37.0));
		box.setScale(glm::vec3(14,5.0, 1.0));
		box.render();

		//Murito CUADRITO 2 ABAJO Derecha
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-7.0 + suma, -11.5, -37.0));
		box.setScale(glm::vec3(13, 5.0, 1.0));
		box.render();

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID24);
		box.setPosition(glm::vec3(17.5 + suma, -6.0, -37.0));
		box.setScale(glm::vec3(13, 6.0, 1.0));
		box.render();

		//cASTILLO Ventana 1M
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(10.5 + suma, -9.0, -37.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();
	

		//Murito CUADRITO 2 arriba de parte baja
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(4.75 + suma, -2.0, -37.0));
		box.setScale(glm::vec3(38.5, 2.0, 1.0));
		box.render();

		//cASTILLO puerta 2M
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(0.50 + suma, -9.0, -37.0));
		box.setScale(glm::vec3(2.0, 12.0, 1.0));
		box.render();


		//cASTILLO Ventana 1M
		glBindTexture(GL_TEXTURE_2D, textureID25);
		box.setPosition(glm::vec3(-14.0 + suma, -9.0, -37.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();

		//Puerta p
		glBindTexture(GL_TEXTURE_2D, textureID15);
		box.setPosition(glm::vec3(5.75 + suma, -8.5, -37.0));
		box.setScale(glm::vec3(8.5, 11.0, 1.0));
		box.render();

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID24);
		box.setPosition(glm::vec3(-7.0 + suma, -6.0, -37.0));
		box.setScale(glm::vec3(13, 6.0, 1.0));
		box.render();

		////-------------------------Arriba 

		//  pared mitad cocina arriba puierta
		//glBindTexture(GL_TEXTURE_2D, textureID6);
		//box9.setPosition(glm::vec3(10.5 + suma, -2.0, 28.0));
		//box9.setScale(glm::vec3(1.0, 2.0, 15.0));
		//box9.render();

		//------------------Piso Madera -------------------//
		//Piso Q1
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-5.0 + suma, 1.00, -13.0));
		box8.setScale(glm::vec3(20.0, 0.1, 27.0));
		box8.render();
		//Piso Q2
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(15.0 + suma, 1.00, -13.0));
		box8.setScale(glm::vec3(20.0, 0.1, 27.0));
		box8.render();
	

		//Piso Fuera Banio P1
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(15.0 + suma, 1.00, 18.75));
		box8.setScale(glm::vec3(20.0, 0.1, 36.75));
		box8.render();

		//Piso Fuera Banio P2
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-5.0 + suma, 1.00, 8.00));
		box8.setScale(glm::vec3(20.0, 0.1, 14.00));
		box8.render();

		//Piso Banio
		glBindTexture(GL_TEXTURE_2D, textureID61);
		box8.setPosition(glm::vec3(-5.0 + suma, 1.00, 25.50));
		box8.setScale(glm::vec3(20.0, 0.1, 21.00));
		box8.render();

		//Piso sala
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-2.50 + suma, -14.00, -22.50));
		box8.setScale(glm::vec3(25.0, 0.1, 28.0));
		box8.render();

		//Piso sala II
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-2.50 + suma, -14.00, 5.0));
		box8.setScale(glm::vec3(25.0, 0.1, 27.0));
		box8.render();

		//Piso banio abajo
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(17.0 + suma, -14.00, -22.50));
		box8.setScale(glm::vec3(14.0, 0.1, 28.0));
		box8.render();

		//Piso cocina 
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(17.0 + suma, -14.00, 5.0));
		box8.setScale(glm::vec3(14.0, 0.1, 27.0));
		box8.render();

		//Piso atras 
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(-2.50 + suma, -14.00, 27.0));
		box8.setScale(glm::vec3(25.0, 0.1, 17.0));
		box8.render();

		//Piso atras  II
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(17.0 + suma, -14.00, 27.0));
		box8.setScale(glm::vec3(14.0, 0.1, 17.0));
		box8.render();


		/* -----------------------Inician Accesorios ----------------------------------*/

		/*Comedor*/

		//___________________Cuadros  Sala
		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4 + suma, -5.4, -22.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID36);
		box9.setPosition(glm::vec3(-14.4 + suma, -4.5, -19.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID37);
		box9.setPosition(glm::vec3(-14.4 + suma, -6.2, -19.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		//___________________Cuadros  comedor

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4 + suma, -5.4, 4.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4 + suma, -5.4, 8.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4 + suma, -5.4, 12.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		//___________________Cuadros  comedor frente 

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(10.0 + suma, -4.4, 22.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();


		/* Primer Cuarto */

				//Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID32);
		box9.setPosition(glm::vec3(-14.5 + suma, 7.5, -13.0));
		box9.setScale(glm::vec3(0.10, 13.0, 27.0));
		box9.render();


		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-8.5 + suma, 6.0, -0.750));
		box9.setScale(glm::vec3(12.0, 10.0, 2.5));
		box9.render(0, 6);
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.render(6, 6);
		glBindTexture(GL_TEXTURE_2D, textureID115);
		box9.render(12, 6);
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.render(18, 6);
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.render(24, 6);

		//______________________TV
		glBindTexture(GL_TEXTURE_2D, textureID38);
		box9.setPosition(glm::vec3(4.5 + suma, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 3.0, 6.0));
		box9.render();

		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-14.3 + suma, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID34);
		box9.setPosition(glm::vec3(-10.0 + suma, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-10.0 + suma, 1.5, -14.0));
		box9.setScale(glm::vec3(8.3, 1.0, 7.0));
		box9.render();

		//___________________Almohada_1
		glBindTexture(GL_TEXTURE_2D, textureID32);
		cylinder3.setPosition(glm::vec3(-13.6 + suma, 4.0, -12.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_2
		glBindTexture(GL_TEXTURE_2D, textureID34);
		cylinder3.setPosition(glm::vec3(-13.6 + suma, 4.0, -14.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_3
		glBindTexture(GL_TEXTURE_2D, textureID117);
		cylinder3.setPosition(glm::vec3(-13.6 + suma, 4.0, -16.4));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID117);
		cylinder3.setPosition(glm::vec3(-13.1 + suma, 4.0, -13.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//__________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID32);
		cylinder3.setPosition(glm::vec3(-13.1 + suma, 4.0, -15.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.7 + suma, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.7 + suma, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Espejo Cuarto
		glBindTexture(GL_TEXTURE_2D, textureID118);
		box9.setPosition(glm::vec3(-14.38 + suma, 6.5, -5.50));
		box9.setScale(glm::vec3(0.1, 7.0, 3.0));
		box9.render();

		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID120);
		box9.setPosition(glm::vec3(-14.4 + suma, 8.4, -15.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();


		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.5 + suma, 2.5, -22.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.5 + suma, 2.5, -26.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.5 + suma, 4.45, -24.00));
		box9.setScale(glm::vec3(2.0, 0.4, 4.20));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-14.4 + suma, 2.00, -24.00));
		box9.setScale(glm::vec3(0.1, 1.0, 4.20));
		box9.render();

		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID117);
		box9.setPosition(glm::vec3(-5.0 + suma, 1.05, -14.00));
		box9.setScale(glm::vec3(8.0, 0.05, 14.00));
		box9.render();


		/* Segundo Cuarto Cuarto De Niño */

		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(23.0 + suma, 6.0, -02.750));
		box9.setScale(glm::vec3(3.0, 10.0, 6.0));
		box9.render(0, 6);
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.render(6, 6);
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.render(12, 6);
		glBindTexture(GL_TEXTURE_2D, textureID115);
		box9.render(18, 6);
		glBindTexture(GL_TEXTURE_2D, textureID115);
		box9.render(24, 6);


		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-14.3 + 38.7 + suma, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID116);
		box9.setPosition(glm::vec3(-10.0 + 30.1 + suma, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-10.0 + 30 + suma, 1.5, -14.0));
		box9.setScale(glm::vec3(8.3, 1.0, 7.0));
		box9.render();

		//___________________Almohada_1
		glBindTexture(GL_TEXTURE_2D, textureID7);
		cylinder3.setPosition(glm::vec3(-10.0 + 34 + suma, 4.0, -11.6));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Almohada_2
		glBindTexture(GL_TEXTURE_2D, textureID43);
		cylinder3.setPosition(glm::vec3(-10.0 + 34 + suma, 4.0, -13.8));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_3
		glBindTexture(GL_TEXTURE_2D, textureID7);
		cylinder3.setPosition(glm::vec3(-10.0 + 34 + suma, 4.0, -16.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID43);
		cylinder3.setPosition(glm::vec3(-10.5 + 34 + suma, 4.0, -12.7));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID7);
		cylinder3.setPosition(glm::vec3(-10.5 + 34 + suma, 4.0, -14.9));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.7 + 37.4 + suma, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.7 + 37.4 + suma, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.5 + 30 + suma, 2.5, -01.00));
		box9.setScale(glm::vec3(0.20, 3.5, 02.5));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-15.5 + 28 + suma, 2.5, -01.00));
		box9.setScale(glm::vec3(0.20, 3.5, 02.5));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-13.5 + 28 + suma, 4.45, -01.00));
		box9.setScale(glm::vec3(4.20, 0.4, 2.50));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID114);
		box9.setPosition(glm::vec3(-14.4 + 28.9 + suma, 2.00, -0.00));
		box9.setScale(glm::vec3(4.20, 1.0, 0.1));
		box9.render();


		/*---------- Cocina Muebles-------------*/


		//  Base de Mesa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -11.50, 28.00));
		box9.setScale(glm::vec3(1.0, 5.0, 15.0));
		box9.render();
		//Mueble madera  der
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.63 + suma, -11.0, 14.50 + x));
		box.setScale(glm::vec3(3.0, 6.00, 6.0));
		box.render();

		//Estufaaaaaaa
		glBindTexture(GL_TEXTURE_2D, textureID62);
		box.setPosition(glm::vec3(22.63 + suma, -11.0, 7.70 + x));
		box.setScale(glm::vec3(3.0, 6.00, 7.50 ));
		box.render();

		//Mueble madera izq
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.6 + suma, -11.0, 1.00 + x));
		box.setScale(glm::vec3(3.0, 6.00, 6.0));
		box.render();
		
		//Estufa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.6 + suma, -11.0, 6.800 + x));
		box.setScale(glm::vec3(3.0, 6.00, 5.6));
		box9.render();


		//--Arriba
		//Mueble madera  der
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.63 + suma, -2.5, 13.50 + x));
		box.setScale(glm::vec3(3.0, 3.00, 8.9));
		box.render();

		//Mueble madera  izq
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.6 + suma, -2.5, 1.00 + x));
		box.setScale(glm::vec3(3.0, 3.00, 6.0));
		box.render();

		//Arriba Estufa mueble
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.6 + suma, -2.25, 6.800 + x));//.25
		box.setScale(glm::vec3(3.0, 2.50, 5.6));
		box.render();
		//Arriba Estufa grasa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.1 + suma, -3.75, 6.800 + x));//.25
		box.setScale(glm::vec3(4.0, 0.50, 5.6));
		box.render();

		//Mueble madera  izqcosas  
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(16.0 + suma, -11.0, 16.00 + x ));
		box.setScale(glm::vec3(7.0, 6.00, 3.0));
		box.render();

		//Mueble madera izqcosas  arriba
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(16.0 + suma, -2.5, 16.00 + x));
		box.setScale(glm::vec3(7.0, 3.00, 3.0));
		box.render();

		//microondaas
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.5 + suma, -7.25, 16.750 + x));
		box.setScale(glm::vec3(3.0, 1.50, 1.5));
		box.render();

		//mesa
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(10.5 + suma, -9.00, 9.00 + x));
		box.setScale(glm::vec3(3.5, 0.20, 17.50));
		box.render();

		/*----------------------------------------Dia de Muertos-------------------------------------------------*/

		//Mesa del Altar 
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.0 + suma, -10.5, -35.00 + x ));
		box.setScale(glm::vec3(4.0, 7.00, 15.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(18.0 + suma, -11.5, -35.00 + x));
		box.setScale(glm::vec3(4.0, 5.00, 15.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(14.0 + suma, -12.5, -35.00 + x));
		box.setScale(glm::vec3(4.0, 3.00, 15.0));
		box.render();
		//Papel picado
		glBindTexture(GL_TEXTURE_2D, textureID104);
		box.setPosition(glm::vec3(11.9 + suma, -12.5, -40.00 + x));
		box.setScale(glm::vec3(0.01, 3.00, 4.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID105);
		box.setPosition(glm::vec3(11.9 + suma, -12.5, -40.00 + x+4.5));
		box.setScale(glm::vec3(0.01, 3.00, 4.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID106);
		box.setPosition(glm::vec3(11.9 + suma, -12.5, -40.00 + x + 9));
		box.setScale(glm::vec3(0.01, 3.00, 4.0));
		box.render();
		//Fondo Altat
		glBindTexture(GL_TEXTURE_2D, textureID110);
		box9.setPosition(glm::vec3(24.0 + suma, -4.0, -22.0));
		box9.setScale(glm::vec3(0.05, 5.0, 28.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID110);
		box9.setPosition(glm::vec3(24.0 + suma, -4.0, 7.0));
		box9.setScale(glm::vec3(0.05, 5.0, 28.0));
		box9.render();
		//______________________Cuadro Altar
		glBindTexture(GL_TEXTURE_2D, textureID123);
		box9.setPosition(glm::vec3(24.0 + suma, -5.0, -17.0));
		box9.setScale(glm::vec3(0.15, 4.5, 4.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID124);
		box9.setPosition(glm::vec3(24.0 + suma, -5.0, -12.0));
		box9.setScale(glm::vec3(0.15, 4.5, 4.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID125);
		box9.setPosition(glm::vec3(24.0 + suma, -5.0, -22.0));
		box9.setScale(glm::vec3(0.15, 4.5, 4.0));
		box9.render();
		//Cilindros Fuego Veladoras izqu
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(21.0 + suma, -6.62, -10.0));
		cylinder2.setScale(glm::vec3(0.7, 0.90, 0.70));
		cylinder2.render();
		//Cilindros Fuego Veladoras izqu 2
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(17.0 + suma, -8.62, -10.0));
		cylinder2.setScale(glm::vec3(0.7, 0.90, 0.70));
		cylinder2.render();
		//Cilindros Fuego Veladoras izqu 3
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(13.0 + suma, -10.62, -10.0));
		cylinder2.setScale(glm::vec3(0.7, 0.90, 0.70));
		cylinder2.render();


		//Cilindros Fuego Veladoras  der
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(21.0 + suma, -6.620, -24.0));
		cylinder2.setScale(glm::vec3(0.7, 0.90, 0.70));
		cylinder2.render();
		//Cilindros Fuego Veladoras  der 2
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(17.0 + suma, -8.620, -24.0));
		cylinder2.setScale(glm::vec3(0.7, 0.90, 0.70));
		cylinder2.render();

		//Cilindros Fuego Veladoras  der 3
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(13.0 + suma, -10.620, -24.0));
		cylinder2.setScale(glm::vec3(0.7, 0.90, 0.70));
		cylinder2.render();

		//Frutas Amarillas 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(23.5 + suma, -6.680, -22.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas verde 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(23.5 + suma, -6.680, -20.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		
		//Veladora
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(22.0 + suma, -6.680, -19.0));
		cylinder2.setScale(glm::vec3(0.6, 0.80, 0.60));
		cylinder2.render();

		//Pan Muerto
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(22.0 + suma, -7.00, -17.0));
		cylinder2.setScale(glm::vec3(2.0, 0.30, 2.00));
		cylinder2.render();

		//VeladoraII
		glBindTexture(GL_TEXTURE_2D, textureID6);
		cylinder2.setPosition(glm::vec3(22.0 + suma, -6.680, -15.0));
		cylinder2.setScale(glm::vec3(0.6, 0.80, 0.60));
		cylinder2.render();
		
		//Frutas verde 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(23.5 + suma, -6.680, -14.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas roja 
		glBindTexture(GL_TEXTURE_2D, textureID122);
		sphere1.setPosition(glm::vec3(23.5 + suma, -6.680, -12.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();

		
		//Frutas Amarillas 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(19.5 + suma, -8.680, -21.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas verde 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(19.5 + suma, -8.680, -19.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas roja 
		glBindTexture(GL_TEXTURE_2D, textureID122);
		sphere1.setPosition(glm::vec3(19.5 + suma, -8.680, -17.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas Amarillas 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(19.5 + suma, -8.680, -15.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas verde 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(19.5 + suma, -8.680, -13.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();


		//Frutas Amarillas 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(15.5 + suma, -10.680, -22.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas Verdes 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(15.5 + suma, -10.680, -20.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas Rojo 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(15.5 + suma, -10.6820, -18.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas Amarillas 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(15.5 + suma, -10.6820, -16.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas Verdes 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(15.5 + suma, -10.6820, -14.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();
		//Frutas Rojo 
		glBindTexture(GL_TEXTURE_2D, textureID47);
		sphere1.setPosition(glm::vec3(15.5 + suma, -10.6820, -12.0));
		sphere1.setScale(glm::vec3(0.6, 0.60, 0.60));
		sphere1.render();

		//Comida p1
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(21.0 + suma, -7.0, -21.0));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(21.00 + suma, -7.00, -13.0));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();

		//Comida p2
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(17.00 + suma, -9.00, -20.0));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(17.00 + suma, -9.00, -14.0));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(17.00 + suma, -9.00, -17.0));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();

		//Comida p3
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(13.00 + suma, -11.00, -21.5));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();
		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(13.00 + suma, -11.00, -12.0));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();

		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(13.00 + suma, -11.00, -15.5));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();

		//
		glBindTexture(GL_TEXTURE_2D, textureID121);
		cylinder2.setPosition(glm::vec3(13.00 + suma, -11.00, -18.5));
		cylinder2.setScale(glm::vec3(1.2, 0.17, 2.00));
		cylinder2.render();

		//Calaveras Azucar
		/*Nivel 3*/
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box.setPosition(glm::vec3(15.00 + suma, -10.50, -23.0));
		box.setScale(glm::vec3(1.0, 1.0, 1.00));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box.setPosition(glm::vec3(15.00 + suma, -10.50, -11.0));
		box.setScale(glm::vec3(1.0, 1.0, 1.00));
		box.render();

		/*Nivel 2*/
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box.setPosition(glm::vec3(18.00 + suma, -8.50, -23.0));
		box.setScale(glm::vec3(1.0, 1.0, 1.00));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box.setPosition(glm::vec3(18.00 + suma, -8.50, -11.0));
		box.setScale(glm::vec3(1.0, 1.0, 1.00));
		box.render();

		/*Nivel 1*/
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box.setPosition(glm::vec3(022.00 + suma, -6.50, -23.0));
		box.setScale(glm::vec3(1.0, 1.0, 1.00));
		box.render();
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box.setPosition(glm::vec3(22.00 + suma, -6.50, -11.0));
		box.setScale(glm::vec3(1.0, 1.0, 1.00));
		box.render();

		//Aircraf Real
		glm::mat4 Air = glm::mat4(1.0);
		Air = glm::translate(Air, glm::vec3(70.0, -10.0, -55.0));
		//Air = glm::scale(Air, glm::vec3(0.10, 0.10, 0.10));
		ModelAircraft.render(Air);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Modelo de pruebas
		glm::mat4 silla = glm::mat4(1.0);
		silla = glm::translate(silla, glm::vec3(-12.0, 2.0, 8.0));
		silla = glm::scale(silla, glm::vec3(0.10, 0.10, 0.10));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		ModelEjemplo.render(silla);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);



		//////////////Models Complex Render
		glm::mat4 matrixModelRock = glm::mat4(1.0);
		matrixModelRock = glm::translate(matrixModelRock, glm::vec3(63.0, -14.0, -60.0));
		modelRock.render(matrixModelRock);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE);
		/////Esto es para las vias del tren
		glm::mat4 matrixModelRailroad = glm::mat4(1.0);
		matrixModelRailroad = glm::translate(matrixModelRailroad, glm::vec3(73.0, -14.0, -45.0));
		modelRailRoad.render(matrixModelRailroad);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		//Alberc
		glm::mat4 modelAgua = glm::mat4(1.0);
		modelAgua = glm::translate(modelAgua, glm::vec3(60.0, -14.1, -61.0));
		modelAgua = glm::scale(modelAgua, glm::vec3(20.0, 0.01, 20.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID2);
		///Le cambiamos el shader con multiples luces
		shaderMulLighting.setFloat("offsetX", offX);
		box2.render(modelAgua);
		glBindTexture(GL_TEXTURE_2D, 0);
		shaderMulLighting.setFloat("offsetX", 0);

		/*Personajes Nacimiento*/
		//Burro
		glm::mat4 Burro = glm::mat4(1.0);
		Burro = glm::translate(Burro, glm::vec3(-13.3, 1.75, 7.0));
		Burro = glm::scale(Burro, glm::vec3(1.7, 2.0, 1.7));
		Burro = glm::rotate(Burro, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID74);
		box3.render(18, 6, Burro);
		glBindTexture(GL_TEXTURE_2D, 0);
		//Maria
		glm::mat4 Maria = glm::mat4(1.0);
		Maria = glm::translate(Maria, glm::vec3(-13.2, 1.75, 5.80));
		Maria = glm::scale(Maria, glm::vec3(2.0, 2.4, 2.0));
		Maria = glm::rotate(Maria, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID78);
		box3.render(18, 6, Maria);
		glBindTexture(GL_TEXTURE_2D, 0);
		//Jose
		glm::mat4 Jose = glm::mat4(1.0);
		Jose = glm::translate(Jose, glm::vec3(-13.2, 1.75, 3.9));
		Jose = glm::scale(Jose, glm::vec3(2.0, 2.4, 2.0));
		Jose = glm::rotate(Jose, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID76);
		box3.render(18, 6, Jose);
		glBindTexture(GL_TEXTURE_2D, 0);

		///Nino
		glm::mat4 Nino = glm::mat4(1.0);
		Nino = glm::translate(Nino, glm::vec3(-13.3, 2.15, 4.80));
		Nino = glm::scale(Nino, glm::vec3(1.3, 1.7, 1.3));
		Nino = glm::rotate(Nino, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID79);
		box3.render(18, 6, Nino);
		glBindTexture(GL_TEXTURE_2D, 0);


		//Toro
		glm::mat4 Toro = glm::mat4(1.0);
		Toro = glm::translate(Toro, glm::vec3(-13.3, 1.75, 2.7));
		Toro = glm::scale(Toro, glm::vec3(1.7, 2.0, 1.7));
		Toro = glm::rotate(Toro, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID77);
		box3.render(18, 6, Toro);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Pastor
		glm::mat4 Pastor = glm::mat4(1.0);
		Pastor = glm::translate(Pastor, glm::vec3(-10.0, 1.6, 10.0));
		Pastor = glm::scale(Pastor, glm::vec3(1.7, 1.9, 1.7));
		Pastor = glm::rotate(Pastor, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID80);
		box3.render(18, 6, Pastor);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Pastor2
		glm::mat4 Pastor2 = glm::mat4(1.0);
		Pastor2 = glm::translate(Pastor2, glm::vec3(-5.5, 1.6, 3.0));
		Pastor2 = glm::scale(Pastor2, glm::vec3(1.7, 1.9, 1.7));
		Pastor2 = glm::rotate(Pastor2, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID81);
		box3.render(18, 6, Pastor2);
		glBindTexture(GL_TEXTURE_2D, 0);

		//ReyMago
		glm::mat4 ReyMago = glm::mat4(1.0);
		ReyMago = glm::translate(ReyMago, glm::vec3(-8.0, 1.6, 5.0));
		ReyMago = glm::scale(ReyMago, glm::vec3(0.7, 1.4, 0.7));
		ReyMago = glm::rotate(ReyMago, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID82);
		box3.render(18, 6, ReyMago);
		glBindTexture(GL_TEXTURE_2D, 0);


		//ReyMago2
		glm::mat4 ReyMago2 = glm::mat4(1.0);
		ReyMago2 = glm::translate(ReyMago2, glm::vec3(-6.0, 1.6, 6.0));
		ReyMago2 = glm::scale(ReyMago2, glm::vec3(0.70, 1.4, 0.7));
		ReyMago2 = glm::rotate(ReyMago2, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID83);
		box3.render(18, 6, ReyMago2);
		glBindTexture(GL_TEXTURE_2D, 0);


		//Mago3
		glm::mat4 ReyMago3 = glm::mat4(1.0);
		ReyMago3 = glm::translate(ReyMago3, glm::vec3(-5.0, 1.6, 7.0));
		ReyMago3 = glm::scale(ReyMago3, glm::vec3(0.7, 1.4, 0.70));
		ReyMago3 = glm::rotate(ReyMago3, glm::radians(180.0f), glm::vec3(0.0, 0.0, 01.00));
		glBindTexture(GL_TEXTURE_2D, textureID84);
		box3.render(18, 6, ReyMago3);
		glBindTexture(GL_TEXTURE_2D, 0);

		//paja
		glm::mat4 paja = glm::mat4(1.0);
		paja = glm::translate(paja, glm::vec3(-012.8, 6.50, 4.75));
		paja = glm::scale(paja, glm::vec3(2.0, 3.0, 7.550));
		paja = glm::rotate(paja, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID85);
		box3.render(18, 6, paja);
		glBindTexture(GL_TEXTURE_2D, 0);

		//Animales

		//pollo
		glm::mat4 pollo = glm::mat4(1.0);
		pollo = glm::translate(pollo, glm::vec3(-3.5, 1.6, 3.0));
		pollo = glm::scale(pollo, glm::vec3(0.80, 1.0, 0.80));
		pollo = glm::rotate(pollo, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID89);
		box3.render(18, 6, pollo);
		glBindTexture(GL_TEXTURE_2D, 0);

		//siervo
		glm::mat4 siervo = glm::mat4(1.0);
		siervo = glm::translate(siervo, glm::vec3(-5.5, 1.6, 4.50));
		siervo = glm::scale(siervo, glm::vec3(1.0, 1.0, 1.0));
		siervo = glm::rotate(siervo, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID90);
		box3.render(18, 6, siervo);
		glBindTexture(GL_TEXTURE_2D, 0);

		//conejo
		glm::mat4 conejo = glm::mat4(1.0);
		conejo = glm::translate(conejo, glm::vec3(-6.5, 1.6, 8.50));
		conejo = glm::scale(conejo, glm::vec3(1.1, 1.1, 1.1));
		conejo = glm::rotate(conejo, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		glBindTexture(GL_TEXTURE_2D, textureID91);
		box3.render(18, 6, conejo);
		glBindTexture(GL_TEXTURE_2D, 0);

		/*Nacimiento*/

		//Alberc
		glm::mat4 aguaNacimiento = glm::mat4(1.0);
		aguaNacimiento = glm::translate(aguaNacimiento, glm::vec3(-8.5, 1.05, 10.0));
		aguaNacimiento = glm::scale(aguaNacimiento, glm::vec3(15.0, 0.01, 10.0));
		// Se activa la textura del agua
		glBindTexture(GL_TEXTURE_2D, textureID2);
		///Le cambiamos el shader con multiples luces
		shaderMulLighting.setFloat("offsetX", offX);
		box2.render(aguaNacimiento);
		glBindTexture(GL_TEXTURE_2D, 0);
		shaderMulLighting.setFloat("offsetX", 0);

		//________________________Pastle
		glBindTexture(GL_TEXTURE_2D, textureID73);
		cylinder3.setPosition(glm::vec3(-8.0, 1.05, 5.50));
		cylinder3.setScale(glm::vec3(14.0, 0.05, 12.00));
		cylinder3.render();

		//________________________paja cuna nino dios
		glBindTexture(GL_TEXTURE_2D, textureID8);
		box9.setPosition(glm::vec3(-13.0, 1.1, 4.80));
		box9.setScale(glm::vec3(1.20, 1.20, 2.00));
		box9.render();

		//Casita de Madera Nino izq
		glBindTexture(GL_TEXTURE_2D, textureID88);
		box9.setPosition(glm::vec3(-13.50, 3.10, 7.70));
		box9.setScale(glm::vec3(3.0, 4.0, 0.15));
		box9.render();

		//Casita de Madera Nino der 
		glBindTexture(GL_TEXTURE_2D, textureID88);
		box9.setPosition(glm::vec3(-13.5, 3.10, 1.70));
		box9.setScale(glm::vec3(3.0, 4.0, 0.15));
		box9.render();

		//Casita de Madera Nino techo
		glBindTexture(GL_TEXTURE_2D, textureID88);
		box9.setPosition(glm::vec3(-013.5, 5.10, 4.75));
		box9.setScale(glm::vec3(3.0, 0.2, 6.00));
		box9.render();

		//Casita de Madera Nino piso
		glBindTexture(GL_TEXTURE_2D, textureID88);
		box9.setPosition(glm::vec3(-013.5, 1.150, 4.75));
		box9.setScale(glm::vec3(3.0, 0.1, 6.00));
		box9.render();

		//Fondo Casa
		glBindTexture(GL_TEXTURE_2D, textureID86);
		box9.setPosition(glm::vec3(-14.4, 3.2, 4.750));
		box9.setScale(glm::vec3(0.1, 4.0, 6.0));
		box9.render();

		//Estrella dew Belen
		glBindTexture(GL_TEXTURE_2D, textureID87);
		box9.setPosition(glm::vec3(-14.5, 6.0, 8.00));
		box9.setScale(glm::vec3(0.1, 10.0, 14.0));
		box9.render();


		// Render for the eclipse car
		glm::mat4 modelMatrixEclipseChasis = glm::mat4(modelMatrixEclipse);
		modelMatrixEclipseChasis = glm::scale(modelMatrixEclipse, glm::vec3(0.5, 0.5, 0.5));
		modelEclipseChasis.render(modelMatrixEclipseChasis);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 modelMatrixFrontalWheels = glm::mat4(modelMatrixEclipseChasis);
		modelMatrixFrontalWheels = glm::translate(modelMatrixFrontalWheels, glm::vec3(0.0, 1.05813, 4.11483));
		modelMatrixFrontalWheels = glm::rotate(modelMatrixFrontalWheels, rotWheelsY, glm::vec3(0, 1, 0));
		modelMatrixFrontalWheels = glm::rotate(modelMatrixFrontalWheels, rotWheelsX, glm::vec3(1, 0, 0));
		modelMatrixFrontalWheels = glm::translate(modelMatrixFrontalWheels, glm::vec3(0.0, -1.05813, -4.11483));
		modelEclipseFrontalWheels.render(modelMatrixFrontalWheels);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 modelMatrixRearWheels = glm::mat4(modelMatrixEclipseChasis);
		modelMatrixRearWheels = glm::translate(modelMatrixRearWheels, glm::vec3(0.0, 1.05813, -4.35157));
		modelMatrixRearWheels = glm::rotate(modelMatrixRearWheels, rotWheelsX, glm::vec3(1, 0, 0));
		modelMatrixRearWheels = glm::translate(modelMatrixRearWheels, glm::vec3(0.0, -1.05813, 4.35157));
		modelEclipseRearWheels.render(modelMatrixRearWheels);
		glActiveTexture(GL_TEXTURE0);

		// Helicopter
		glm::mat4 modelMatrixHeliChasis = glm::mat4(modelMatrixHeli);
		modelHeliChasis.render(modelMatrixHeliChasis);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 modelMatrixHeliHeli = glm::mat4(modelMatrixHeliChasis);

		glActiveTexture(GL_TEXTURE0);

		// Lambo car
		glm::mat4 modelMatrixLambo = glm::mat4(1.0);
		modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(-43.0, -14.0, -72.0));
		modelMatrixLambo = glm::scale(modelMatrixLambo, glm::vec3(5.0, 5.0, 5.0));
		modelLambo.render(modelMatrixLambo);
		glActiveTexture(GL_TEXTURE0);
		glm::mat4 modelMatrixLamboLeftDor = glm::mat4(modelMatrixLambo);
		modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(1.08676, 0.707316, 0.982601));
		modelMatrixLamboLeftDor = glm::rotate(modelMatrixLamboLeftDor, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
		modelMatrixLamboLeftDor = glm::translate(modelMatrixLamboLeftDor, glm::vec3(-1.08676, -0.707316, -0.982601));
		modelLamboLeftDor.render(modelMatrixLamboLeftDor);
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 modelMatrixLamboRightDor = glm::mat4(modelMatrixLambo);
		modelMatrixLamboRightDor = glm::translate(modelMatrixLamboRightDor, glm::vec3(4.08676, 0.707316, 0.982601));
		modelMatrixLamboRightDor = glm::rotate(modelMatrixLamboRightDor, glm::radians(dorRotCount), glm::vec3(1.0, 0, 0));
		modelMatrixLamboRightDor = glm::translate(modelMatrixLamboRightDor, glm::vec3(-4.08676, -0.707316, -0.982601));
		modelLamboRightDor.render(modelMatrixLamboRightDor);
		glActiveTexture(GL_TEXTURE0);


		glm::mat4 modelMatrixLamboWheelFrente = glm::mat4(modelMatrixLambo);
		modelMatrixLamboWheelFrente = glm::translate(modelMatrixLamboWheelFrente, glm::vec3(-0.20, 0.3722, -1.670));
		modelMatrixLamboWheelFrente = glm::rotate(modelMatrixLamboWheelFrente, rotWheelsXlamb, glm::vec3(1.0, 0, 0));
		modelMatrixLamboWheelFrente = glm::translate(modelMatrixLamboWheelFrente, glm::vec3(-0.20, 0.3722, -1.670));
		modelLamboWheelsFrontal.render(modelMatrixLamboWheelFrente);
		glActiveTexture(GL_TEXTURE0);


		glm::mat4 modelMatrixLamboWheelAtras = glm::mat4(modelMatrixLambo);
		modelMatrixLamboWheelAtras = glm::translate(modelMatrixLamboWheelAtras, glm::vec3(-0.20, 0.3722, 1.359));
		modelMatrixLamboWheelAtras = glm::rotate(modelMatrixLamboWheelAtras, rotWheelsXlamb, glm::vec3(1.0, 0, 0));
		modelMatrixLamboWheelAtras = glm::translate(modelMatrixLamboWheelAtras, glm::vec3(-0.20, 0.3722, 1.359));
		modelLamboWheelsRear.render(modelMatrixLamboWheelAtras);
		glActiveTexture(GL_TEXTURE0);

		rotWheelsXlamb += 0.05;
		/////////////////////////////////////////////////////


		if (angle > 2 * M_PI)
			angle = 0.0;
		else
			angle += 0.0001;

		/*Objetos de Sala y comedor Casa 1*/

		//Mesa Comedor
		glm::mat4 mesa = glm::mat4(1.0);
		mesa = glm::translate(mesa, glm::vec3(-4.0, -14.0, 10.0));
		mesa = glm::scale(mesa, glm::vec3(8.0, 6.5, 8.00));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		modelMesa.render(mesa);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 sofas = glm::mat4(1.0);
		sofas = glm::translate(sofas, glm::vec3(-7.0, -12.0, -33.0));
		sofas = glm::scale(sofas, glm::vec3(2.50, 3.00, 3.00));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		ModelSofa.render(sofas);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		glm::mat4 sofas2 = glm::mat4(1.0);
		sofas2 = glm::translate(sofas2, glm::vec3(-7.0, -12.0, -10.0));
		sofas2 = glm::scale(sofas2, glm::vec3(2.50, 2.50, 2.50));
		sofas2 = glm::rotate(sofas2, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		ModelSofa.render(sofas2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		glm::mat4 sofa = glm::mat4(1.0);
		sofa = glm::translate(sofa, glm::vec3(-12.0, -14.0, -21.0));
		sofa = glm::scale(sofa, glm::vec3(1.8000, 2.000, 2.00));
		sofa = glm::rotate(sofa, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		ModelSofaP.render(sofa);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Silla Cafe
		glm::mat4 sillaC = glm::mat4(1.0);
		sillaC = glm::translate(sillaC, glm::vec3(-6.0, -11.0, 20.0));
		sillaC = glm::scale(sillaC, glm::vec3(0.0060, 0.0060, 0.0060));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		ModelSilla.render(sillaC);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelMesa

		glm::mat4 Mesa2 = glm::mat4(1.0);
		Mesa2 = glm::translate(Mesa2, glm::vec3(-3.0, -15.0, -21.0));
		Mesa2 = glm::scale(Mesa2, glm::vec3(8.0, 8.0, 8.00));
		ModelMesa.render(Mesa2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//--------------------------
		/*Objetos de Sala y comedor Casa 2*/

		//Mesa Comedor
		glm::mat4 mesa2 = glm::mat4(1.0);
		mesa2 = glm::translate(mesa2, glm::vec3(-4.0 + suma, -14.0, 10.0));
		mesa2 = glm::scale(mesa2, glm::vec3(8.0, 6.5, 8.00));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		modelMesa.render(mesa2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		glm::mat4 sofas3 = glm::mat4(1.0);
		sofas3 = glm::translate(sofas3, glm::vec3(-7.0, -12.0, -33.0));
		sofas3 = glm::scale(sofas3, glm::vec3(2.50, 3.00, 3.00));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		ModelSofa.render(sofas3);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		glm::mat4 sofas4 = glm::mat4(1.0);
		sofas4 = glm::translate(sofas4, glm::vec3(-7.0 + suma, -12.0, -10.0));
		sofas4 = glm::scale(sofas4, glm::vec3(2.50, 2.50, 2.50));
		sofas4 = glm::rotate(sofas4, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		ModelSofa.render(sofas4);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		glm::mat4 sofa2 = glm::mat4(1.0);
		sofa2 = glm::translate(sofa2, glm::vec3(-12.0 + suma, -14.0, -21.0));
		sofa2 = glm::scale(sofa2, glm::vec3(1.8000, 2.000, 2.00));
		sofa2 = glm::rotate(sofa2, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		ModelSofaP.render(sofa);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Silla Cafe
		glm::mat4 sillaC2 = glm::mat4(1.0);
		sillaC2 = glm::translate(sillaC2, glm::vec3(-6.0 + suma, -11.0, 20.0));
		sillaC2 = glm::scale(sillaC2, glm::vec3(0.0060, 0.0060, 0.0060));
		//silla = glm::rotate(silla, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.00));
		ModelSilla.render(sillaC2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelMesa

		glm::mat4 Mesa3 = glm::mat4(1.0);
		Mesa3 = glm::translate(Mesa3, glm::vec3(-3.0 + suma, -15.0, -21.0));
		Mesa3 = glm::scale(Mesa3, glm::vec3(8.0, 8.0, 8.00));
		ModelMesa.render(Mesa3);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		/*Objetos para Casa 1*/

		//WC
		glm::mat4 wc = glm::mat4(1.0);
		wc = glm::translate(wc, glm::vec3(-13.0, 1.1, 24.5));
		wc = glm::scale(wc, glm::vec3(1.5, 1.5, 1.50));
		ModelWC.render(wc);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Silla de trabajo 
		glm::mat4 SillaT = glm::mat4(1.0);
		SillaT = glm::translate(SillaT, glm::vec3(-10.0, 1.1, -23.0));
		SillaT = glm::scale(SillaT, glm::vec3(0.05, 0.05, 0.05));
		ModelEjemplo.render(SillaT);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Jardinera
		glm::mat4 Jardinera = glm::mat4(1.0);
		Jardinera = glm::translate(Jardinera, glm::vec3(-3.0, -15.0, -47.0));
		Jardinera = glm::scale(Jardinera, glm::vec3(0.2, 0.2, 0.20));
		Modeljardinera.render(Jardinera);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Jardinera BANIO
		glm::mat4 JardineraB = glm::mat4(1.0);
		JardineraB = glm::translate(JardineraB, glm::vec3(3.5, 1.1, 35.00));
		JardineraB = glm::scale(JardineraB, glm::vec3(0.2, 0.2, 0.20));
		Modeljardinera.render(JardineraB);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		/*Objetos para casa 2 */
		//WC
		glm::mat4 wc2 = glm::mat4(1.0);
		wc2 = glm::translate(wc2, glm::vec3(-13.0 + suma, 1.1, 24.5));
		wc2 = glm::scale(wc2, glm::vec3(1.5, 1.5, 1.50));
		ModelWC.render(wc2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Silla de trabajo 
		glm::mat4 SillaT2 = glm::mat4(1.0);
		SillaT2 = glm::translate(SillaT2, glm::vec3(-10.0 + suma, 1.1, -23.0));
		SillaT2 = glm::scale(SillaT2, glm::vec3(0.05, 0.05, 0.05));
		ModelEjemplo.render(SillaT2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Jardinera
		glm::mat4 Jardinera2 = glm::mat4(1.0);
		Jardinera2 = glm::translate(Jardinera2, glm::vec3(-3.0 + suma, -15.0, -47.0));
		Jardinera2 = glm::scale(Jardinera2, glm::vec3(0.2, 0.2, 0.20));
		Modeljardinera.render(Jardinera2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Jardinera BANIO
		glm::mat4 JardineraB2 = glm::mat4(1.0);
		JardineraB2 = glm::translate(JardineraB2, glm::vec3(3.5 + suma, 1.1, 35.00));
		JardineraB2 = glm::scale(JardineraB2, glm::vec3(0.2, 0.2, 0.20));
		Modeljardinera.render(JardineraB2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		/*Objetos de Navidad*/

		//PINATA
		glm::mat4 pinata = glm::mat4(1.0);
		pinata = glm::translate(pinata, glm::vec3(-12.0, 9.0, -44.0));
		pinata = glm::scale(pinata, glm::vec3(1.2, 1.2, 1.20));
		ModelPinata.render(pinata);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//PINATA2
		glm::mat4 pinata2 = glm::mat4(1.0);
		pinata2 = glm::translate(pinata2, glm::vec3(5.0, 9.0, -44.0));
		pinata2 = glm::scale(pinata2, glm::vec3(1.2, 1.2, 1.20));
		ModelPinata.render(pinata2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//PINATA3
		glm::mat4 pinata3 = glm::mat4(1.0);
		pinata3 = glm::translate(pinata3, glm::vec3(24.0, 9.0, -44.0));
		pinata3 = glm::scale(pinata3, glm::vec3(1.2, 1.2, 1.20));
		ModelPinata.render(pinata3);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//PINATA4
		glm::mat4 pinata4 = glm::mat4(1.0);
		pinata4 = glm::translate(pinata4, glm::vec3(42.0, 9.0, -44.0));
		pinata4 = glm::scale(pinata4, glm::vec3(1.2, 1.2, 1.20));
		ModelPinata.render(pinata4);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelPinoNavidad
		glm::mat4 pino = glm::mat4(1.0);
		pino = glm::translate(pino, glm::vec3(-11.0, -14.0, 30.0));
		pino = glm::scale(pino, glm::vec3(3.0, 3.0, 3.00));
		ModelPinoNavidad.render(pino);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//estrella
		glm::mat4 Bell = glm::mat4(1.0);
		Bell = glm::translate(Bell, glm::vec3(-12.0, -10.0, 28.0));
		Bell = glm::scale(Bell, glm::vec3(0.10, 0.10, 0.100));
		ModelBell.render(Bell);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelPinoNavidad
		glm::mat4 esfera = glm::mat4(1.0);
		esfera = glm::translate(esfera, glm::vec3(-11.0, -4.0, 30.0));
		esfera = glm::scale(esfera, glm::vec3(0.0250, 0.0250, 0.02500));
		ModelEstrella.render(esfera);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		//ModelChimenea
		glm::mat4 fuego = glm::mat4(1.0);
		fuego = glm::translate(fuego, glm::vec3(-3.0, -14.0, 35.0));
		fuego = glm::rotate(fuego, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		fuego = glm::scale(fuego, glm::vec3(0.10, 0.100, 0.100));
		ModelChimenea.render(fuego);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);
		//////////////////////////////////////////////////////////////////////////////////
		//ModelBaston
		glm::mat4 Baston = glm::mat4(1.0);
		Baston = glm::translate(Baston, glm::vec3(-11.0, -10.0, 28.0));
		Baston = glm::rotate(Baston, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.00));
		Baston = glm::scale(Baston, glm::vec3(0.50, 0.50, 0.500));
		ModelBaston.render(Baston);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelCaballito
		glm::mat4 caballo = glm::mat4(1.0);
		caballo = glm::translate(caballo, glm::vec3(-4.0, -10.0, 25.0));
		caballo = glm::rotate(caballo, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		caballo = glm::scale(caballo, glm::vec3(0.10, 0.100, 0.100));
		ModelCaballito.render(caballo);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);



		//ModelCalceta
		glm::mat4 calceta = glm::mat4(1.0);
		calceta = glm::translate(calceta, glm::vec3(-5.0, -10.0, 20.0));
		calceta = glm::rotate(calceta, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.00));
		calceta = glm::scale(calceta, glm::vec3(2.10, 2.100, 2.100));
		ModelCalceta.render(calceta);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelDinosaur
		glm::mat4 dinor = glm::mat4(1.0);
		dinor = glm::translate(dinor, glm::vec3(0.0, -10.0, 25.0));
		dinor = glm::rotate(dinor, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		dinor = glm::scale(dinor, glm::vec3(1.10, 1.100, 1.100));
		ModelDinosaur.render(dinor);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		//ModelHat
		glm::mat4 hat = glm::mat4(1.0);
		hat = glm::translate(hat, glm::vec3(-4.0, -8.0, 20.0));
		hat = glm::rotate(hat, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		hat = glm::scale(hat, glm::vec3(0.10, 0.100, 0.100));
		ModelHat.render(hat);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelRegaloDos
		glm::mat4 dos = glm::mat4(1.0);
		dos = glm::translate(dos, glm::vec3(-9.0, -10.0, 25.0));
		//dos = glm::rotate(dos, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		dos = glm::scale(dos, glm::vec3(0.020, 0.0200, 0.0200));
		ModelRegaloDos.render(dos);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		//ModelRegaloUno
		glm::mat4 uno = glm::mat4(1.0);
		uno = glm::translate(uno, glm::vec3(-5.0, -10.0, 25.0));
		//uno = glm::rotate(uno, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		uno = glm::scale(uno, glm::vec3(0.020, 0.0200, 0.0200));
		ModelRegaloUno.render(uno);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelSpiderman
		glm::mat4 spidey = glm::mat4(1.0);
		spidey = glm::translate(spidey, glm::vec3(-4.0, -10.0, 25.0));
		spidey = glm::rotate(spidey, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		spidey = glm::scale(spidey, glm::vec3(1.10, 1.100, 1.100));
		ModelSpiderman.render(spidey);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelNochebuena
		glm::mat4 noceB = glm::mat4(1.0);
		noceB = glm::translate(noceB, glm::vec3(-4.0, -8.0, 15.0));
		noceB = glm::rotate(noceB, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		noceB = glm::scale(noceB, glm::vec3(0.10, 0.100, 0.100));
		ModelNochebuena.render(noceB);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//Esferas
	//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -7.0, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -6, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -4, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -5, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -3, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -4, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -5, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -6, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -7, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-11.0, -8, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-9.0, -9, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-10.0, -10, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();


		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-8.0, -11, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-9.0, -12, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();

		//Roja
		sphereLamp.setScale(glm::vec3(0.35, 0.35, 0.35));
		sphereLamp.setPosition(glm::vec3(-10.0, -13, 30.0));
		sphereLamp.setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		sphereLamp.render();
		sphereLamp.render();

		/*Dia de Muertos*/

		//Fantasma
		glm::mat4 ghost = glm::mat4(modelMatrixFantasma);
		ghost = glm::rotate(modelMatrixFantasma, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		ghost = glm::scale(modelMatrixFantasma, glm::vec3(4.10, 4.100, 4.100));
		modelFantasma.render(ghost);
		glActiveTexture(GL_TEXTURE0);

		//modelCandlestick
		glm::mat4 candelabro = glm::mat4(modelMatrixCandelabro);
		candelabro = glm::rotate(modelMatrixCandelabro, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		candelabro = glm::scale(modelMatrixCandelabro, glm::vec3(1.10, 1.100, 1.100));
		modelCandlestick.render(candelabro);
		glActiveTexture(GL_TEXTURE0);

		//modelSkelet
		glm::mat4 skelet = glm::mat4(modelMatrixCraneo);
		skelet = glm::scale(modelMatrixCraneo, glm::vec3(0.100, 0.100, 0.1000));
		modelSkelet.render(skelet);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		/*Animaciones Navidad*/

		//modelSkelet
		glm::mat4 trineo = glm::mat4(modelMatrixTrineo);
		trineo = glm::scale(modelMatrixTrineo, glm::vec3(0.02, 0.02, 0.020));
		ModelTrineo.render(trineo);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		/*Fin de objetos Navidad*/

		/*Modelos Dia de Muertos
		modelCalabaza;
		modelCandlestick;
		modelMango;
		modelManzana;
		modelSkelet;
		modelSkull_v3;
		*/
		/*fin dia d emuertos*/

		/*********************Objetos para dia de muertos**********************************/
		

		//*********************************************************************************
		/*
		//modelCalabaza
		glm::mat4 cala = glm::mat4(1.0);
		cala = glm::translate(cala, glm::vec3(35.0, -10.0, 25.0));
		cala = glm::rotate(cala, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		cala = glm::scale(cala, glm::vec3(0.10, 0.100, 0.100));
		modelCalabaza.render(cala);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		

		//modelMango
		glm::mat4 mango = glm::mat4(1.0);
		mango = glm::translate(mango, glm::vec3(42, -10.0, 35.0));
		mango = glm::rotate(mango, glm::radians(180.0f), glm::vec3(0.0, 0.0, 0.00));
		mango = glm::scale(mango, glm::vec3(0.10, 0.100, 0.100));
		modelMango.render(mango);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//modelManzana
		glm::mat4 manzana = glm::mat4(1.0);
		manzana = glm::translate(manzana, glm::vec3(40.0, -10.0, 35.0));
		manzana = glm::rotate(manzana, glm::radians(180.0f), glm::vec3(0.0, 0.0, 0.00));
		manzana = glm::scale(manzana, glm::vec3(0.10, 0.100, 0.100));
		modelManzana.render(manzana);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		
		*/
		//modelSkull_v3
		glm::mat4 skelet2 = glm::mat4(1.0);
		skelet2 = glm::translate(skelet2, glm::vec3(35.0, -10.0, 35.0));
		skelet2 = glm::rotate(skelet2, glm::radians(180.0f), glm::vec3(0.0, 0.0, 0.00));
		skelet2 = glm::scale(skelet2, glm::vec3(0.10, 0.100, 0.100));
		modelSkull_v3.render(skelet2);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);


		// Se Dibuja el Skybox
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);

		offX += 0.001;
		dz = 0;
		dza = 0;
		rot0 = 0;
		rota0 = 0;
		rotHelHelY += 0.5;



		switch (state2) {
		case 3:
			//std::cout << "Land the plane" << std::endl;
			//std::cout << offsetAircraftAdvanceII << std::endl;
			modelMatrixHeli = glm::translate(modelMatrixHeli, glm::vec3(0.0, -0.015, 0.00));
			offsetAircraftAdvanceII += 0.01;

			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, -0.249548));
			modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHelHelY, glm::vec3(0, 1, 0));
			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, 0.249548));
			modelHeliHeli.render(modelMatrixHeliHeli);
			glActiveTexture(GL_TEXTURE0);

			if (offsetAircraftAdvanceII > 10.0) {
				offsetAircraftAdvanceII = 0.0;
				state2 = 5;
				break;
			}
			break;
		case 4:
			//std::cout << "Fly" << std::endl;
			//std::cout << offsetAircraftAdvanceII << std::endl;
			modelMatrixHeli = glm::translate(modelMatrixHeli, glm::vec3(0.0, 0.0, 0.02));

			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, -0.249548));
			modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHelHelY, glm::vec3(0, 1, 0));
			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, 0.249548));
			modelHeliHeli.render(modelMatrixHeliHeli);
			glActiveTexture(GL_TEXTURE0);

			offsetAircraftAdvanceII += 0.01;
			if (offsetAircraftAdvanceII > 13.50) {
				offsetAircraftAdvanceII = 0.0;
				state2 = 3;
			}
			break;
		case 5:

			//std::cout << "Stop" << std::endl;
			//std::cout << rotHelHelYStop << std::endl;
			if (offsetAircraftAdvanceII == 0.0) {
				rotHelHelYStop -= 0.10;
				offsetAircraftAdvanceII = 1.0;
			}
			if (offsetAircraftAdvanceII == 1.0) {
				rotHelHelYStop -= 0.05;
			}
			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, -0.249548));
			modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHelHelYStop, glm::vec3(0, 1, 0));
			modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, 0.249548));
			modelHeliHeli.render(modelMatrixHeliHeli);
			glActiveTexture(GL_TEXTURE0);


			if (rotHelHelYStop <= 0.0) {
				rotHelHelY = 0.0;
				state2 = 6;
				break;

			}
			break;
		default:
			break;
		}

		modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, -0.249548));
		//modelMatrixHeliHeli = glm::rotate(modelMatrixHeliHeli, rotHelHelY, glm::vec3(0, 1, 0));
		modelMatrixHeliHeli = glm::translate(modelMatrixHeliHeli, glm::vec3(0.0, 0.0, 0.249548));
		modelHeliHeli.render(modelMatrixHeliHeli);
		glActiveTexture(GL_TEXTURE0);


		/*******************************************
		 * State machines
		 *******************************************/
		 // State machine for eclipse car
		switch (state){
		case 0:
			//std::cout << "Advance" << std::endl;
			//std::cout << offsetAircraftAdvance << std::endl;
			modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(0.0, 0.0, 0.1));
			advanceCount += 0.1;
			rotWheelsX += 0.05;
			rotWheelsY -= 0.02;
			if (rotWheelsY < 0)
				rotWheelsY = 0;
			if (advanceCount > 45.0) {
				advanceCount = 0;
				state = 1;
			}
			break;
		case 1:
			//modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(0.0, 0.0, 0.025));
			//modelMatrixEclipse = glm::rotate(modelMatrixEclipse, glm::radians(0.5f), glm::vec3(0, 1, 0));
			rotCount += 0.5f;
			rotWheelsX += 0.05;
			rotWheelsY += 0.02;
			if (rotWheelsY > 0.25)
				rotWheelsY = 0.25;
			if (rotCount >= 90.0) {
				rotCount = 0;
				state = 0;
			}
			break;
		}

		//FantasmaEnMovimiento
		switch (stadoFantasma) {
		case 0:
			modelMatrixFantasma = glm::translate(modelMatrixFantasma, glm::vec3(0.0, 0.0, 0.1));
			advanceCountFantasma += 0.1;
			if (advanceCountFantasma > 5.0) {
				advanceCountFantasma = 0;
				stadoFantasma = 1;
			}
			break;

		case 1:
			modelMatrixFantasma = glm::translate(modelMatrixFantasma, glm::vec3(0.0, 0.0, 0.01));
			modelMatrixFantasma = glm::rotate(modelMatrixFantasma, glm::radians(0.5f), glm::vec3(0, 1, 0));
			offsetFantasmaRot += 0.05;
			if (offsetFantasmaRot > 90) {
				offsetFantasmaRot = 0.0;
				stadoFantasma = 0;
			}
				
			break;
		}

		//Candelabro
		switch (stadoCandelabro)
		{
		case 0://avanza en una direccion
			posicionCandelabroY = posicionCandelabroInicialY + (velocidadInicialCandelabro * tiempoCandelabro * sin(anguloCandelabro)) - (0.5 * gravedad * tiempoCandelabro * tiempoCandelabro);
			modelMatrixCandelabro = glm::translate(modelMatrixCandelabro, glm::vec3(0.01, posicionCandelabroY, 0.0));
			if (posicionCandelabroY >= 0.0f) {
				tiempoCandelabro += 0.0001f;
			}
			else {
				posicionCandelabroInicialY = 0.0f;
				tiempoCandelabro = 0.0f;
				stadoCandelabro = 1;
			}
			break;
		case 1://avanza en direccion contraria
			posicionCandelabroY = posicionCandelabroInicialY + (velocidadInicialCandelabro * tiempoCandelabro * sin(anguloCandelabro)) - (0.5 * gravedad * tiempoCandelabro * tiempoCandelabro);
			modelMatrixCandelabro = glm::translate(modelMatrixCandelabro, glm::vec3(-0.01, posicionCandelabroY, 0.0));
			if (posicionCandelabroY >= 0.0f) {
				tiempoCandelabro += 0.0001f;
			}
			else {
				posicionCandelabroInicialY = 0.0f;
				tiempoCandelabro = 0.0f;
				stadoCandelabro = 0;
			}
			break;
		default:
			break;
		}

		
		switch (stadoCraneo) {
		case 0://avanza hacia enfrente
			modelMatrixCraneo = glm::translate(modelMatrixCraneo, glm::vec3(0.0, -0.1, 0.0));
			advanceCountCraneo += 0.1f;
			if (advanceCountCraneo > 10.0f) {
				//avanzaCraneo = 0.0f;
				stadoCraneo = 1;
			}
			break;

		case 1://retrosede hacia atras
			modelMatrixCraneo = glm::translate(modelMatrixCraneo, glm::vec3(0.0, 0.1, 0.0));
			advanceCountCraneo -= 0.1f;
			if (advanceCountCraneo < 0.0f) {
				advanceCountCraneo = 0.0f;
				stadoCraneo = 2;
			}
			break;
		case 2:
			modelMatrixCraneo = glm::rotate(modelMatrixCraneo, glm::radians(1.0f), glm::vec3(0, 0, 1));
			offsetCraneoRot += 1;
			if (offsetCraneoRot > 90) {
				stadoCraneo = 0;
				offsetCraneoRot = 0;
			}
		default:
			break;
		}

		switch (stateTrineo) {
		case 0://avanza hacia enfrente
			modelMatrixTrineo = glm::translate(modelMatrixTrineo, glm::vec3(0.10, -0.0, 0.0));
			advanceCountTrineo += 0.20f;
			if (advanceCountTrineo > 45.0f) {
				//avanzaCraneo = 0.0f;
				stateTrineo = 1;
			}
			break;

		case 1://retrosede hacia atras
			modelMatrixTrineo = glm::translate(modelMatrixTrineo, glm::vec3(-0.10, 0.0, 0.0));
			advanceCountTrineo -= 0.1f;
			if (advanceCountTrineo < 0.0f) {
				advanceCountTrineo = 0.0f;
				stateTrineo = 0;
			}
			break;
		}

		// State machine for the lambo car
		switch (stateDoor) {
		case 0:
			dorRotCount += 0.5;
			if (dorRotCount > 75)
				stateDoor = 1;
			break;
		case 1:
			dorRotCount -= 0.5;
			if (dorRotCount < 0) {
				dorRotCount = 0.0;
				stateDoor = 0;
			}
			break;
		}


		//machine state for the tour casa
		if (cambioCamara == 2 || cambioCamara == 3) {
			//TimeManager::Instance().CalculateFrameRate(false);
			deltaTime = TimeManager::Instance().DeltaTime;
			switch (stateHouseRecorrido) {
			case 0:
				recorridoCamara += 0.1;

				if (cambioCamara == 2) {
					cameraHorrorHouseAutomatic->moveFrontCamera(true, deltaTime);
				}
				else if (cambioCamara == 3) {
					cameraChristmastHouseAutomatic->moveFrontCamera(true, deltaTime);
				}

				if (recorridoCamara > 90) {
					recorridoCamara = 0;
					stateHouseRecorrido = 1;
				}
				break;
			case 1:
				giroCamaraY += glm::radians(1.0f);

				if (cambioCamara == 2) {
					cameraHorrorHouseAutomatic->mouseMoveCamera(1.0f, 0.0f, 0.01);
				}
				else if (cambioCamara == 3) {
					//cameraChristmastHouseAutomatic->moveRightCamera(true, deltaTime);
					cameraChristmastHouseAutomatic->mouseMoveCamera(1.0f, 0.0f, 0.01);
				}

				if (giroCamaraY > glm::radians(90.0f)) {
					giroCamaraY = 0.0f;
					stateHouseRecorrido = 0;
				}
				break;
			default:
				break;
			}
		}

		/////////////////////////////

		/////////////////////////////
		/*-------------------------AUDIO----------------------------------*/
		// Libreria de audio
		// openal sound data
		source0Pos[0] = modelMatrixEclipse[3].x;
		source0Pos[1] = modelMatrixEclipse[3].y;
		source0Pos[2] = modelMatrixEclipse[3].z;
		alSourcefv(sources[0], AL_POSITION, source0Pos);
		source1Pos[0] = modelMatrixHeli[3].x;
		source1Pos[1] = modelMatrixHeli[3].y;
		source1Pos[2] = modelMatrixHeli[3].z;
		alSourcefv(sources[1], AL_POSITION, source1Pos);


		// Position listener
		listenerPos[0] = cameraHorrorHouseFree->getPosition().x;
		listenerPos[1] = cameraHorrorHouseFree->getPosition().y;
		listenerPos[2] = cameraHorrorHouseFree->getPosition().z;
		alListenerfv(AL_POSITION, listenerPos);
		// Orientation listener
		listenerOri[0] = cameraHorrorHouseFree->getFront().x;
		listenerOri[1] = cameraHorrorHouseFree->getFront().y;
		listenerOri[2] = cameraHorrorHouseFree->getFront().z;
		listenerOri[3] = cameraHorrorHouseFree->getUp().x;
		listenerOri[4] = cameraHorrorHouseFree->getUp().y;
		listenerOri[5] = cameraHorrorHouseFree->getUp().z;
		alListenerfv(AL_ORIENTATION, listenerOri);

		glfwSwapBuffers(window);
	}
}

int main(int argc, char** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
