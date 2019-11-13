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
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;
GLFWwindow* window;

//Suma para duplicar la casa
float suma = 65.0f;

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

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

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
Model Aircraft;
Model ModelAircraft;
Model ModelMesa;
Model ModelPlanta;
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
, textureID67, textureID68, textureID69, textureID70, textureID71, textureID72;

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

	/*Cosas de Navidad*/

	modelMesa.loadModel("../models/table/table.obj");
	modelMesa.setShader(&shaderMulLighting);

	ModelSilla.loadModel("../models/SillaComedor/Chair.obj");
	ModelSilla.setShader(&shaderMulLighting);

	Modeljardinera.loadModel("../models/Navidad/jardinera/jardinera.obj");
	Modeljardinera.setShader(&shaderMulLighting);

	ModelWC.loadModel("../models/toilet/toilet.obj");
	ModelWC.setShader(&shaderMulLighting);

	ModelPinata.loadModel("../models/Navidad/pinata/pinata.obj");
	ModelPinata.setShader(&shaderMulLighting);
	
	ModelTrineo.loadModel("../models/Navidad/trineo/trineo.obj");
	ModelTrineo.setShader(&shaderMulLighting);

	ModelPinoNavidad.loadModel("../models/Navidad/christmas_tree/Christmas+tree.obj");
	ModelPinoNavidad.setShader(&shaderMulLighting);
	
	ModelEstrella.loadModel("../models/Navidad/bell/11566_Bell_V5_l3.obj");
	ModelEstrella.setShader(&shaderMulLighting);

	//ModelEsfera.loadModel("../models/Navidad/ArbolNavidad/11.obj");
	//ModelEsfera.setShader(&shaderMulLighting);

	/*

	ModelBaston.loadModel("../models/Navidad/baston/baston1.obj");
	ModelBaston.setShader(&shaderMulLighting);

	ModelCaballito.loadModel("../models/Navidad/caballito/caballito.obj");
	ModelCaballito.setShader(&shaderMulLighting);

	

	ModelPinoNavidad.loadModel("../models/Navidad/pino/pine_tree.obj");
	ModelPinoNavidad.setShader(&shaderMulLighting);

	ModelHat.loadModel("../models/Navidad/hat/santa_hat(BLENDER).obj");
	ModelHat.setShader(&shaderMulLighting);

	ModelSpiderman.loadModel("../models/Navidad/spiderman/M-CoC_iOS_HERO_Peter_Parker_Spider-Man_Stark_Enhanced.obj");
	ModelSpiderman.setShader(&shaderMulLighting);

	ModelRegaloUno.loadModel("../models/Navidad/regalo/REGALO_Alex.obj");
	ModelRegaloUno.setShader(&shaderMulLighting);

	ModelRegaloDos.loadModel("../models/Navidad/regalo2/regalo.obj");
	ModelRegaloDos.setShader(&shaderMulLighting);

	ModelRosa.loadModel("../models/Navidad/rosa/rosa.obj");
	ModelRosa.setShader(&shaderMulLighting);

	ModelNochebuena.loadModel("../models/Navidad/nochebuena/nochebuena.obj");
	ModelNochebuena.setShader(&shaderMulLighting);

	

	ModelDinosaur.loadModel("../models/Navidad/Dinosaur/Dinosaur.obj");
	ModelDinosaur.setShader(&shaderMulLighting);

	ModelTren.loadModel("../models/Navidad/rock/rock.obj");
	ModelTren.setShader(&shaderMulLighting);

	ModelTrineo.loadModel("../models/Navidad/trineo/trineo.obj");
	ModelTrineo.setShader(&shaderMulLighting);








	ModelPrueba.loadModel("../models/Navidad/calceta/calceta_roja.obj");
	ModelPrueba.setShader(&shaderMulLighting);
	*/
	/*Fin cosas de Navidad*/

	ModelSofa.loadModel("../models/Navidad/sofa/sofa.obj");
	ModelSofa.setShader(&shaderMulLighting);

	ModelSofaP.loadModel("../models/Navidad/sofap/sofap.obj");
	ModelSofaP.setShader(&shaderMulLighting);

	/*Ubicacion de los modelos*/
	modelRock.loadModel("../models/rock/rock.obj");
	modelRock.setShader(&shaderMulLighting);

	ModelAircraft.loadModel("../models/Aircraft_obj/E 45 Aircraft_obj.obj");
	ModelAircraft.setShader(&shaderMulLighting);

	Aircraft.loadModel("../models/Eclipse/2003eclipse.obj");
	Aircraft.setShader(&shaderMulLighting);

	modelRailRoad.loadModel("../models/railroad/railroad_track.obj");
	modelRailRoad.setShader(&shaderMulLighting);

	modelCami.loadModel("../models/dog/12228_Dog_v1_L2.obj");
	modelCami.setShader(&shaderMulLighting);

	ModelMesa.loadModel("../models/Wood_Table/Wood_Table.obj");
	ModelMesa.setShader(&shaderMulLighting);


	ModelPlanta.loadModel("../models/Helicopter/Mi_24.obj");
	ModelPlanta.setShader(&shaderMulLighting);

	ModelEjemplo.loadModel("../models/silla/10239_Office_Chair_v1_L3.obj");
	ModelEjemplo.setShader(&shaderMulLighting);
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

	//Se inicializan los objetos para el modelo de R2D2
	torsoR2D2.init();
	torsoR2D2.setShader(&shader);
	torsoR2D2.setColor(glm::vec4(255, 255, 255, 255));
	cabezaR2D2.init();
	cabezaR2D2.setShader(&shader);
	cabezaR2D2.setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	articulacionR2D2.init();
	articulacionR2D2.setShader(&shader);
	articulacionR2D2.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	brazoR2D2.init();
	brazoR2D2.setShader(&shader);
	brazoR2D2.setColor(glm::vec4(255, 255, 255, 255));
	pieR2D2.init();
	pieR2D2.setShader(&shader);
	pieR2D2.setColor(glm::vec4(0.6f, 0.6f, 0.6f, 1.0f));

	/*Posicion de la Camara al iniciar*/
	camera->setPosition(glm::vec3(-30.0, 03.0, -10.0));

	/*Se cargan las Texturas*/
	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	// Definiendo la textura a utilizar
	Texture texture1("../Textures/sponge.jpg");
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

	Texture texture8("../Textures/piel.jpg");
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
	Texture texture15("../Textures/seda.jpg");
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

	Texture texture18("../Textures/metal.jpg");
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

	Texture texture24("../Textures/banco.jpg");
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

	Texture texture25("../Textures/teclado.jpg");
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


	Texture texture71("../Textures/logo.png");
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
	/*------------------------------------------------------------------------------------------------------------*/

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

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Destrucción de los VAO, EBO, VBO
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, 0.01);
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

	/////////////////////////
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

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
		shaderColorLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderColorLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderColorLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		shaderTextureLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderTextureLighting.setVectorFloat3("light.ambient",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.diffuse",
			glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTextureLighting.setVectorFloat3("light.specular",
			glm::value_ptr(glm::vec3(0.9, 0.0, 0.0)));

		// Propiedades de la luz para objetos con textura
		shaderMaterialLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMaterialLighting.setVectorFloat3("light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMaterialLighting.setVectorFloat3("light.diffuse", glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderMaterialLighting.setVectorFloat3("light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));

		// Propiedades de la luz para objetos con multiples luces
		///////////////////////////////////////////////////////Intensidad de luz
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 1.0)));
		//SpotLight
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(camera->getFront()));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.1);
		shaderMulLighting.setFloat("spotLights[0].cuadratic", 0.05);
		if (luces >= 5.00) {
			luces = 0.00;
			luces2 = 5.0;
		}
		else {
			/*Luces*/
		// Esto es para la luces pointlights
		//Numero de luces a utilizar de tipo poinlights=3
			shaderMulLighting.setInt("pointLightCount", 11);   //Multiple Light .fs
			//01Verde
			shaderMulLighting.setVectorFloat3("pointLights[0].position", glm::value_ptr((glm::vec3(-14.4, 13, 4.0))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[0].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[0].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[0].constant", luces); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[0].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[0].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//02 Roja
			shaderMulLighting.setVectorFloat3("pointLights[1].position", glm::value_ptr((glm::vec3(-14.4, 13, 4.7))));
			shaderMulLighting.setVectorFloat3("pointLights[1].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[1].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[1].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[1].constant", luces2);
			shaderMulLighting.setFloat("pointLights[1].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[1].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//03 Azul
			shaderMulLighting.setVectorFloat3("pointLights[2].position", glm::value_ptr((glm::vec3(-14.4, 13, 5.4))));
			shaderMulLighting.setVectorFloat3("pointLights[2].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[2].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.1)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[2].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[2].constant", luces);
			shaderMulLighting.setFloat("pointLights[2].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[2].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//04 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[3].position", glm::value_ptr((glm::vec3(-14.4, 13, 6.1))));
			shaderMulLighting.setVectorFloat3("pointLights[3].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[3].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[3].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[3].constant", luces2);
			shaderMulLighting.setFloat("pointLights[3].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[3].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//05  Morada
			shaderMulLighting.setVectorFloat3("pointLights[4].position", glm::value_ptr((glm::vec3(-14.4, 13, 6.8))));
			shaderMulLighting.setVectorFloat3("pointLights[4].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[4].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.1)));
			shaderMulLighting.setVectorFloat3("pointLights[4].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("pointLights[4].constant", luces);
			shaderMulLighting.setFloat("pointLights[4].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[4].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//06Verde
			shaderMulLighting.setVectorFloat3("pointLights[5].position", glm::value_ptr((glm::vec3(-14.4, 13, 7.5))));  //  position de la luz
			shaderMulLighting.setVectorFloat3("pointLights[5].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[5].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[5].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[5].constant", luces2); //Casi siempre a 1
			shaderMulLighting.setFloat("pointLights[5].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[5].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//07 Roja
			shaderMulLighting.setVectorFloat3("pointLights[6].position", glm::value_ptr((glm::vec3(-14.4, 13, 8.2))));
			shaderMulLighting.setVectorFloat3("pointLights[6].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[6].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.0, 0.0)));  //Red
			shaderMulLighting.setVectorFloat3("pointLights[6].light.specular", glm::value_ptr(glm::vec3(0.6, 0.0, 0.0)));
			shaderMulLighting.setFloat("pointLights[6].constant", luces);
			shaderMulLighting.setFloat("pointLights[6].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[6].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//08 Azul
			shaderMulLighting.setVectorFloat3("pointLights[7].position", glm::value_ptr((glm::vec3(-14.4, 13, 8.9))));
			shaderMulLighting.setVectorFloat3("pointLights[7].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[7].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.0, 0.1)));  //BLUE
			shaderMulLighting.setVectorFloat3("pointLights[7].light.specular", glm::value_ptr(glm::vec3(0.0, 0.0, 0.6)));
			shaderMulLighting.setFloat("pointLights[7].constant", luces2);
			shaderMulLighting.setFloat("pointLights[7].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[7].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//09 Amarilla
			shaderMulLighting.setVectorFloat3("pointLights[8].position", glm::value_ptr((glm::vec3(-14.4, 13, 9.6))));
			shaderMulLighting.setVectorFloat3("pointLights[8].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[8].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[8].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.0)));
			shaderMulLighting.setFloat("pointLights[8].constant", luces);
			shaderMulLighting.setFloat("pointLights[8].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[8].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//010  Morada
			shaderMulLighting.setVectorFloat3("pointLights[9].position", glm::value_ptr((glm::vec3(-14.4, 13, 10.3))));
			shaderMulLighting.setVectorFloat3("pointLights[9].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[9].light.diffuse", glm::value_ptr(glm::vec3(0.01, 0.01, 0.1)));
			shaderMulLighting.setVectorFloat3("pointLights[9].light.specular", glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
			shaderMulLighting.setFloat("pointLights[9].constant", luces2);
			shaderMulLighting.setFloat("pointLights[9].linear", 0.04);
			shaderMulLighting.setFloat("pointLights[9].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;
			//////LUZ nueva 11
			shaderMulLighting.setVectorFloat3("pointLights[10].position", glm::value_ptr((glm::vec3(-14.4, 13, 11.0))));
			shaderMulLighting.setVectorFloat3("pointLights[10].light.ambient", glm::value_ptr(glm::vec3(0.001, 0.001, 0.001)));
			shaderMulLighting.setVectorFloat3("pointLights[10].light.diffuse", glm::value_ptr(glm::vec3(0.0, 0.01, 0.0)));
			shaderMulLighting.setVectorFloat3("pointLights[10].light.specular", glm::value_ptr(glm::vec3(0.0, 0.6, 0.0))); //Brilla la luz
			shaderMulLighting.setFloat("pointLights[10].constant", luces);
			shaderMulLighting.setFloat("pointLights[10].linear", 1.14);
			shaderMulLighting.setFloat("pointLights[10].quadratic", 0.004);
			luces2 -= 0.001;
			luces += 0.001;

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
		/*Cadena de luces*/
		glBindTexture(GL_TEXTURE_2D, textureID4);
		box.setPosition(glm::vec3(15.0, 15.04, -45.04));
		box.setScale(glm::vec3(60.0, 0.050, 0.0050));
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
		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4, -5.4, -22.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID36);
		box9.setPosition(glm::vec3(-14.4, -4.5, -19.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID37);
		box9.setPosition(glm::vec3(-14.4, -6.2, -19.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		//___________________Cuadros  comedor

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4, -5.4, 4.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4, -5.4, 8.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4, -5.4, 12.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		//___________________Cuadros  comedor frente 

		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(10.0, -4.4, 22.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();



		/* init  Sala */

		//______________________TV Sala
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box9.setPosition(glm::vec3(10.0, -6.0, -21.0));
		box9.setScale(glm::vec3(0.15, 4.5, 8.0));
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
		glBindTexture(GL_TEXTURE_2D, textureID47);
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
		glBindTexture(GL_TEXTURE_2D, textureID47);
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



		/*------------------------------------------------------------Fin--------------------------w---------------------------------*/

		/*

		glm::mat4 modelCylinder = glm::mat4(1.0);
		modelCylinder = glm::translate(modelCylinder,
			glm::vec3(-3.0, 0.0, 0.0));
		// Envolvente desde el indice 0, el tamanio es 20 * 20 * 6
		// Se usa la textura 1 ( Bon sponja)
		glBindTexture(GL_TEXTURE_2D, textureID1);
		cylinder2.render(0, cylinder2.getSlices() * cylinder2.getStacks() * 6,
			modelCylinder);
		// Tapa Superior desde el indice : 20 * 20 * 6, el tamanio de indices es 20 * 3
		// Se usa la textura 2 ( Agua )
		glBindTexture(GL_TEXTURE_2D, textureID2);
		cylinder2.render(cylinder2.getSlices() * cylinder2.getStacks() * 6,
			cylinder2.getSlices() * 3, modelCylinder);
		// Tapa inferior desde el indice : 20 * 20 * 6 + 20 * 3, el tamanio de indices es 20 * 3
		// Se usa la textura 3 ( Goku )
		glBindTexture(GL_TEXTURE_2D, textureID3);
		cylinder2.render(
			cylinder2.getSlices() * cylinder2.getStacks() * 6
			+ cylinder2.getSlices() * 3, cylinder2.getSlices() * 3,
			modelCylinder);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Render del cubo con textura de ladrillos y con repeticion en x
		glm::mat4 cubeTextureModel = glm::mat4(1.0);
		cubeTextureModel = glm::translate(cubeTextureModel,
			glm::vec3(3.0, 2.0, 3.0));
		glBindTexture(GL_TEXTURE_2D, textureID4);
		shaderTexture.setVectorFloat2("scaleUV",
			glm::value_ptr(glm::vec2(2.0, 1.0)));
		box3.render(cubeTextureModel);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Render del cyindro con materiales
		glm::mat4 cylinderMaterialModel = glm::mat4(1.0);
		cylinderMaterialModel = glm::translate(cylinderMaterialModel, glm::vec3(3.0, 2.0, -3.0));
		shaderMaterialLighting.setVectorFloat3("material.ambient", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.diffuse", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.specular", glm::value_ptr(glm::vec3(0.727811f, 0.626959f, 0.626959f)));
		shaderMaterialLighting.setFloat("material.shininess", 76.8f);
		cylinderMaterials.render(cylinderMaterialModel);

		glm::mat4 boxMaterialModel = glm::mat4(1.0f);
		boxMaterialModel = glm::translate(boxMaterialModel, glm::vec3(-3.0, 2.0, -3.0));
		shaderMaterialLighting.setVectorFloat3("material.ambient", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.diffuse", glm::value_ptr(glm::vec3(0.61424f, 0.04136f, 0.04136f)));
		shaderMaterialLighting.setVectorFloat3("material.specular", glm::value_ptr(glm::vec3(0.727811f, 0.626959f, 0.626959f)));
		shaderMaterialLighting.setFloat("material.shininess", 76.8f);
		boxMaterials.render(boxMaterialModel);

		*/

		//El AirCraft
		//glm::mat4 matrixAircraft = glm::mat4(1.0);
		//matrixAircraft = glm::translate(matrixAircraft, glm::vec3(60.0, -10.0, -55.0));
		Aircraft.render(matrixModelAircraft);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

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
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(15.0 + suma, 0.0, 36.5));
		box.setScale(glm::vec3(60.0, 30.0, 2.0));
		box.render();

		//Piso
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box8.setPosition(glm::vec3(15.0 + suma, -15.0, 0.0));
		box8.setScale(glm::vec3(60.0, 2.0, 75.0));
		box8.render();

		//aTecho
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box8.setPosition(glm::vec3(15.0 + suma, 15.0, 0.0));
		box8.setScale(glm::vec3(61.0, 2.0, 90.0));
		box8.render();

		//Pared lateral 1 Derecha AbajoD
		box9.setPosition(glm::vec3(-15.0 + suma, -7.5, 0.0));
		box9.setScale(glm::vec3(1.0, 17.0, 75.0));
		box9.render();

		//Pared lateral 1 Derecha Arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(-15.0 + suma, 8.0, 5.00));
		box9.setScale(glm::vec3(1.0, 16.0, 65.0));
		box9.render();

		//Pared lateral 2 Izquierda
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box10.setPosition(glm::vec3(45.0 + suma, 0.0, 0.0));
		box10.setScale(glm::vec3(1.0, 32.0, 75.0));
		box10.render();


		//Pared medio por escaleras
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(24.75 + suma, 7.5, -18.00));
		box9.setScale(glm::vec3(0.5, 13.0, 39.0));
		box9.render();

		//Piso intermedio
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box8.setPosition(glm::vec3(5.0 + suma, 0.0, 0.0));
		box8.setScale(glm::vec3(40.0, 2.0, 90.0));
		box8.render();
		/*Fin de la Estructura de la casa*/


		/* ------------ Escaleras --------------------*/

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(26.0 + suma, -0.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(28.0 + suma, -2.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(30.0 + suma, -4.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(32.0 + suma, -6.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(34.0 + suma, -8.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(36.0 + suma, -10.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();

		//escalon
		glBindTexture(GL_TEXTURE_2D, textureID7);
		box9.setPosition(glm::vec3(38.0 + suma, -12.5, 33.0));
		box9.setScale(glm::vec3(3.0, 1.0, 5.0));
		box9.render();


		/* ------------ Fin de Escaleras --------------------*/

		/* ----------------- Barandal -----------------------*/
		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(-15.0 + suma, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Murito 1
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-5.0 + suma, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();

		//Murito 2
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(-15.0 + suma, 3.5, -36.250));
		box.setScale(glm::vec3(1.0, 5.0, 17.5));
		box.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(-15.0 + suma, 6.0, -28.0));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(5.0 + suma, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Murito 3
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(15.0 + suma, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();



		/*------------ Fin Barandal --------------------------*/

		/* ----------------- Ventana Superior con puerta DERECHA --------------------*/


		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(-8.0 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(11, 6.0, 1.0));
		box.render();

		//Murito arriba  izquierda y derecha
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(4.5 + suma, 13.0, -27.0));
		box.setScale(glm::vec3(38.0, 2.0, 1.0));
		box.render();

		//Murito 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.5 + suma, 3.0, -27.0));
		box.setScale(glm::vec3(14.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-1.5 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-14.0 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(1.0, 6.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(2.0 + suma, 6.5, -27.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Fin de Ventana Superior con puerta ---------------------*/


		/* ---------- Ventana Superior con puerta izquierda   ---------------------*/

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(18.25 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(10.5, 6.0, 1.0));
		box.render();
		//Murito 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(18.0 + suma, 3.0, -27.0));
		box.setScale(glm::vec3(14.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(12.0 + suma, 9.0, -27.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(24.0 + suma, 10.0, -27.0));
		box.setScale(glm::vec3(1.0, 8.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(8.25 + suma, 6.5, -27.0));
		box.setScale(glm::vec3(5.5, 11.0, 1.0));
		box.render();

		/* ---------- Fin de Ventana Superior con puerta izquierda ---------------------*/

		// Division de Cuartos Arriba 

		//Pared lateral superior que divide cuartos 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(5.0 + suma, 7.0, -13.5));
		box9.setScale(glm::vec3(1.0, 15.0, 28.0)); //60
		box9.render();

		/* ---------- Cuarto Derecho Entrada ---------------------*/

		//Murito derecheco de frente
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.5 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Murito arriba  izquierda y derecha dentro casa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(4.5 + suma, 13.0, 1.0));
		box.setScale(glm::vec3(40.0, 2.0, 1.0));
		box.render();

		//mURO 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(5.0 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();

		//Puerta
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(2.0 + suma, 6.5, 1.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		/* ---------- Fin Cuarto Derecho Entrada ---------------------*/


		//Murito izuierdo de frente
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.5 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Puerta --
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(8.00 + suma, 6.5, 1.0));
		box.setScale(glm::vec3(5.0, 11.0, 1.0));
		box.render();

		//Murito cuarto pelis
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(38.0 + suma, 6.0, 1.0));
		box.setScale(glm::vec3(14.0, 12.00, 1.0));
		box.render();

		//Puerta -- pelis
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(28.0 + suma, 6.5, 1.0));
		box.setScale(glm::vec3(6.0, 11.0, 1.0));
		box.render();

		//Murito arriba  PELIS dentro casa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(35 + suma, 13.0, 1.0));
		box.setScale(glm::vec3(20.0, 2.0, 1.0));
		box.render();

		/* ---------- Cuarto izquierdo Entrada ---------------------*/

		/*----------------------Baño ------------------------------*/

		//Pared frente de escaleras banio
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(5.0 + suma, 7.0, 25.25));
		box9.setScale(glm::vec3(1.0, 15.0, 20.5));
		box9.render();

		//Murito Baño entrada
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.5 + suma, 6.0, 15.25));
		box.setScale(glm::vec3(14.0, 12.00, 0.5));
		box.render();

		//Murito arriba  izquierda y derecha dentro banio
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-5.0 + suma, 13.0, 15.25));
		box.setScale(glm::vec3(19.0, 2.0, 0.5));
		box.render();

		//Forro de arriba barrita
		glBindTexture(GL_TEXTURE_2D, textureID63);
		box.setPosition(glm::vec3(-5.0 + suma, 13.0, 15.55));
		box.setScale(glm::vec3(19.0, 2.00, 0.025));
		box.render();

		//Puerta BANIO
		glBindTexture(GL_TEXTURE_2D, textureID22);
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

		/*----------------Barandal sala pelis--------------------*/

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(45.0 + suma, 6.0, -38.0));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(25.0 + suma, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Esfera
		glBindTexture(GL_TEXTURE_2D, textureID13);
		sphere2.setPosition(glm::vec3(45.0 + suma, 6.0, -44.5));
		sphere2.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere2.render();

		//Murito 1
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(35.0 + suma, 3.5, -44.5));
		box.setScale(glm::vec3(20.0, 5.0, 1.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(45.0 + suma, 3.5, -41.25));
		box.setScale(glm::vec3(1.0, 5.0, 7.0));
		box.render();

		/*----------------Fin Barandal sala  pelis--------------------*/

		/*----------------Ventana sala pelis--------------------*/

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(32.5 + suma, 9.0, -37.0));
		box.setScale(glm::vec3(11, 6.0, 1.0));
		box.render();

		//Murito 2 enfrente del brandal
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(32.5 + suma, 3.0, -37.0));
		box.setScale(glm::vec3(15.0, 6.0, 1.0));
		box.render();

		//Murito 2 enfrente del brandal arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(32.5 + suma, 13.0, -37.0));
		box.setScale(glm::vec3(15.0, 2.0, 1.0));
		box.render();

		//Murito CUADRITO 1
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(26.00 + suma, 9.0, -37.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO 2 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(39.00 + suma, 9.0, -37.0));
		box.setScale(glm::vec3(2.0, 6.0, 1.0));
		box.render();

		//Murito CUADRITO Arriba de puerta
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(42.25 + suma, 13.0, -37.0));
		box.setScale(glm::vec3(4.5, 2.0, 1.0));
		box.render();

		//Puerta PELIS
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(42.25 + suma, 6.5, -37.0));
		box.setScale(glm::vec3(4.5, 11.0, 1.0));
		box.render();

		/*---------------- Fin Ventana sala pelis--------------------*/

		/*--------------------Sala de Pelis--------------------- */

		//Piso intermedio pelis
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box8.setPosition(glm::vec3(35.0 + suma, 0.0, -15.0));
		box8.setScale(glm::vec3(21.0, 2.0, 60.0));
		box8.render();

		//Murito 2 enfrente de las escaleras
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box.setPosition(glm::vec3(34.75 + suma, 3.5, 14.75));
		box.setScale(glm::vec3(19.50, 5.0, 0.5));
		box.render();

		//Barandal por Escaleras
		//Pared frente de escaleras banio
		glBindTexture(GL_TEXTURE_2D, textureID23);
		box9.setPosition(glm::vec3(24.75 + suma, 3.5, 22.5));
		box9.setScale(glm::vec3(0.5, 5.0, 16.0));
		box9.render();

		/*------------------Fin sala Pelis----------------------*/

		//// -------------  Frente  ------------------------- 

		//Muro ABAJO IZQUIERDA Funciona como pared del baño
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.0 + suma, -8.5, -37.0));
		box.setScale(glm::vec3(14, 15.0, 1.0));
		box.render();

		//Murito CUADRITO 2 ABAJO Derecha
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-7.0 + suma, -11.5, -37.0));
		box.setScale(glm::vec3(13, 5.0, 1.0));
		box.render();

		//Murito CUADRITO 2 arriba de parte baja
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-2.25 + suma, -2.0, -37.0));
		box.setScale(glm::vec3(24.5, 2.0, 1.0));
		box.render();

		//cASTILLO puerta 2M
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(0.50 + suma, -9.0, -37.0));
		box.setScale(glm::vec3(2.0, 12.0, 1.0));
		box.render();


		//cASTILLO Ventana 1M
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(-14.0 + suma, -9.0, -37.0));
		box.setScale(glm::vec3(1.0, 12.0, 1.0));
		box.render();

		//Puerta p
		glBindTexture(GL_TEXTURE_2D, textureID30);
		box.setPosition(glm::vec3(5.75 + suma, -8.5, -37.0));
		box.setScale(glm::vec3(8.5, 11.0, 1.0));
		box.render();

		//Venatha entrada
		glBindTexture(GL_TEXTURE_2D, textureID13);
		box.setPosition(glm::vec3(-7.0 + suma, -6.0, -37.0));
		box.setScale(glm::vec3(13, 6.0, 1.0));
		box.render();

		///--------------------------------------Cocina-----------------------------------------------////
		//Murito CUADRITO 2 ABAJO IZQUIERDA
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.0 + suma, -8.5, 18.0));
		box.setScale(glm::vec3(14, 15.0, 1.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(17.0 + suma, -8.5, -8.0));
		box.setScale(glm::vec3(14, 15.0, 1.0));
		box.render();

		//  pared  cocina completa der
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -7.5, 14.75));
		box9.setScale(glm::vec3(1.0, 14.0, 5.5));
		box9.render();

		//  pared mitad cocina
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -11.5, 6.75));
		box9.setScale(glm::vec3(1.0, 5.0, 10.5));
		box9.render();

		//  pared mitad cocina arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -2.0, 6.75));
		box9.setScale(glm::vec3(1.0, 2.0, 10.5));
		box9.render();

		//  pared  cocina completa izq
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -7.5, 0.5));
		box9.setScale(glm::vec3(1.0, 14.0, 2.0));
		box9.render();

		////-------------------------Arriba 

		//  pared mitad cocina arriba puierta
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -2.0, -4.00));
		box9.setScale(glm::vec3(1.0, 2.0, 7.0));
		box9.render();


		//  pared mitad cocina arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -2.0, -11.50));
		box9.setScale(glm::vec3(1.0, 2.0, 6.0));
		box9.render();


		// -------------------Cochera -----------------------//
		glBindTexture(GL_TEXTURE_2D, textureID12);
		box.setPosition(glm::vec3(34.75 + suma, -9.5, -37.0));
		box.setScale(glm::vec3(19.5, 13.0, 1.0));
		box.render();
		//murito arriba
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(34.75 + suma, -2.0, -37.0));
		box.setScale(glm::vec3(19.5, 2.0, 1.0));
		box.render();

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
		//Piso Q3 p1
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(35.0 + suma, 1.00, -23.0));
		box8.setScale(glm::vec3(20.0, 0.1, 27.0));
		box8.render();
		//Piso Q3 p2W
		glBindTexture(GL_TEXTURE_2D, textureID17);
		box8.setPosition(glm::vec3(35.0 + suma, 1.00, 2.5));
		box8.setScale(glm::vec3(20.0, 0.1, 24.0));
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

		/*Entrada por estacionamiento*/
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -2.0, 32.750));
		box9.setScale(glm::vec3(1.0, 2.0, 6.5));
		box9.render();

		//  pared  grande
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -7.5, 24.0));
		box9.setScale(glm::vec3(1.0, 14.0, 11.0));
		box9.render();

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



		/* init  Sala */

		//______________________TV Sala
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box9.setPosition(glm::vec3(10.0 + suma, -6.0, -21.0));
		box9.setScale(glm::vec3(0.15, 4.5, 8.0));
		box9.render();

	

		/* Primer Cuarto */

		//_________________Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID32);
		box9.setPosition(glm::vec3(-14.5 + suma, 7.5, -13.0));
		box9.setScale(glm::vec3(0.10, 13.0, 27.0));
		box9.render();
		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-8.5 + suma, 6.0, -0.750));
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
		box9.setPosition(glm::vec3(4.5 + suma, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 3.0, 6.0));
		box9.render();

		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-14.3 + suma, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID34);
		box9.setPosition(glm::vec3(-10.0 + suma, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID29);
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
		glBindTexture(GL_TEXTURE_2D, textureID33);
		cylinder3.setPosition(glm::vec3(-13.6 + suma, 4.0, -16.4));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//__________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID33);
		cylinder3.setPosition(glm::vec3(-13.1 + suma, 4.0, -13.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//__________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID32);
		cylinder3.setPosition(glm::vec3(-13.1 + suma, 4.0, -15.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.7 + suma, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.7 + suma, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Espejo Cuarto
		glBindTexture(GL_TEXTURE_2D, textureID39);
		box9.setPosition(glm::vec3(-14.38 + suma, 6.5, -5.50));
		box9.setScale(glm::vec3(0.1, 7.0, 3.0));
		box9.render();

		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID35);
		box9.setPosition(glm::vec3(-14.4 + suma, 8.4, -15.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID36);
		box9.setPosition(glm::vec3(-14.4 + suma, 7.5, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID37);
		box9.setPosition(glm::vec3(-14.4 + suma, 9.2, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.5 + suma, 2.5, -22.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.5 + suma, 2.5, -26.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-13.5 + suma, 4.45, -24.00));
		box9.setScale(glm::vec3(2.0, 0.4, 4.20));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID29);
		box9.setPosition(glm::vec3(-14.4 + suma, 2.00, -24.00));
		box9.setScale(glm::vec3(0.1, 1.0, 4.20));
		box9.render();

		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID33);
		box9.setPosition(glm::vec3(-5.0 + suma, 1.05, -14.00));
		box9.setScale(glm::vec3(8.0, 0.05, 14.00));
		box9.render();


		/* Segundo Cuarto Cuarto De Niño */
		//_________________Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID42);
		box9.setPosition(glm::vec3(24.5 + suma, 7.5, -13.0));
		box9.setScale(glm::vec3(0.10, 13.0, 27.0));
		box9.render();

		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(23.0 + suma, 6.0, -02.750));
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
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box9.setPosition(glm::vec3(4.5 + 1.0 + suma, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 3.0, 6.0));
		box9.render();

		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-14.3 + 38.7 + suma, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID45);
		box9.setPosition(glm::vec3(-10.0 + 30.1 + suma, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID40);
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
		glBindTexture(GL_TEXTURE_2D, textureID40);
		cylinder3.setPosition(glm::vec3(-10.5 + 34 + suma, 4.0, -14.9));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();

		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.7 + 37.4 + suma, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.7 + 37.4 + suma, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Espejo Cuarto
		glBindTexture(GL_TEXTURE_2D, textureID44);
		box9.setPosition(glm::vec3(-14.38 + 38.8 + suma, 6.5, -22.50));
		box9.setScale(glm::vec3(0.1, 7.0, 3.0));
		box9.render();

		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.5 + 30 + suma, 2.5, -01.00));
		box9.setScale(glm::vec3(0.20, 3.5, 02.5));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-15.5 + 28 + suma, 2.5, -01.00));
		box9.setScale(glm::vec3(0.20, 3.5, 02.5));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-13.5 + 28 + suma, 4.45, -01.00));
		box9.setScale(glm::vec3(4.20, 0.4, 2.50));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID40);
		box9.setPosition(glm::vec3(-14.4 + 28.9 + suma, 2.00, -0.00));
		box9.setScale(glm::vec3(4.20, 1.0, 0.1));
		box9.render();

		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID48);
		box9.setPosition(glm::vec3(-14.4 + 38.8 + suma, 8.4, -15.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID46);
		box9.setPosition(glm::vec3(-14.4 + 38.8 + suma, 8.4, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID43);
		cylinder3.setPosition(glm::vec3(-5.0 + 20.5 + suma, 1.05, -14.00));
		cylinder3.setScale(glm::vec3(8.0, 0.05, 14.00));
		cylinder3.render();


		/* Tercer Cuarto Cuarto */
		//_________________Pared Cuarto diferente Color
		glBindTexture(GL_TEXTURE_2D, textureID52);
		box9.setPosition(glm::vec3(25.0 + suma, 7.5, -18.00));
		box9.setScale(glm::vec3(0.10, 13.0, 37.0));
		box9.render();

		//__________________Ropero
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(38.5 + suma, 6.0, -0.750));
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
		glBindTexture(GL_TEXTURE_2D, textureID47);
		box9.setPosition(glm::vec3(4.95 + 39.5 + suma, 7.5, -14.0));
		box9.setScale(glm::vec3(0.15, 4.0, 8.0));
		box9.render();


		//___________________Cabecera cama
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-14.3 + 39.5 + suma, 3.50, -14.0));
		box9.setScale(glm::vec3(0.25, 6.0, 7.0));
		box9.render();

		//__________________Cama
		glBindTexture(GL_TEXTURE_2D, textureID54);
		box9.setPosition(glm::vec3(-10.0 + 39.5 + suma, 2.75, -14.0));
		box9.setScale(glm::vec3(8.30, 1.50, 7.0));
		box9.render();

		//___________________Base cama
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-10.0 + 39.5 + suma, 1.5, -14.0));
		box9.setScale(glm::vec3(8.3, 1.0, 7.0));
		box9.render();


		//___________________Almohada
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.6 + 39.5 + suma, 4.5, -12.0));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_2
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.6 + 39.5 + suma, 4.5, -14.2));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_3
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.6 + 39.5 + suma, 4.5, -16.4));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_4
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.1 + 39.5 + suma, 4.5, -13.1));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();
		//___________________Almohada_5
		glBindTexture(GL_TEXTURE_2D, textureID16);
		cylinder3.setPosition(glm::vec3(-13.1 + 39.5 + suma, 4.5, -15.3));
		cylinder3.setScale(glm::vec3(0.5, 1.5, 2.5));
		cylinder3.render();


		//___________________Mueble izquierdo
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.7 + 39.5 + suma, 2.0, -9.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Mueble Derecho 
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.7 + 39.5 + suma, 2.0, -18.50));
		box9.setScale(glm::vec3(1.5, 2.5, 2.0));
		box9.render();

		//___________________Cuadros
		glBindTexture(GL_TEXTURE_2D, textureID56);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 8.4, -17.00));
		box9.setScale(glm::vec3(0.1, 3.2, 3.0));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID57);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 8.4, -14.1));
		box9.setScale(glm::vec3(0.1, 3.6, 1.8));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID59);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 7.5, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID58);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 9.2, -12.00));
		box9.setScale(glm::vec3(0.1, 1.5, 1.7));
		box9.render();

		glBindTexture(GL_TEXTURE_2D, textureID60);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 8.35, -9.5));
		box9.setScale(glm::vec3(0.1, 1.5, 2.5));
		box9.render();
		//_____________________Mesa Estudio 
		//_____________________Lados
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.5 + 39.5 + suma, 2.5, -24.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.5 + 39.5 + suma, 2.5, -32.00));
		box9.setScale(glm::vec3(2.0, 3.5, 0.2));
		box9.render();

		//______________________Tapa Mesa
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-13.5 + 39.5 + suma, 4.45, -28.00));
		box9.setScale(glm::vec3(2.0, 0.4, 8.20));
		box9.render();

		//______________________Tapa abajo
		glBindTexture(GL_TEXTURE_2D, textureID50);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 2.00, -28.00));
		box9.setScale(glm::vec3(0.1, 1.0, 8.20));
		box9.render();

		//________________________Alfombra
		glBindTexture(GL_TEXTURE_2D, textureID55);
		box9.setPosition(glm::vec3(-5.0 + 39.5 + suma, 1.05, -14.00));
		box9.setScale(glm::vec3(8.0, 0.05, 14.00));
		box9.render();

		//_________________________Pizarron
		glBindTexture(GL_TEXTURE_2D, textureID53);
		box9.setPosition(glm::vec3(-14.4 + 39.5 + suma, 8.4, -28.00));
		box9.setScale(glm::vec3(0.1, 6.0, 10.0));
		box9.render();

		/*---------- Cocina Muebles-------------*/

		//Refrijerador
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.5 + suma, -8.5, -5.00));
		box.setScale(glm::vec3(3.0, 11.00, 5.0));
		box9.render();


		//Mueble madera  der
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.63 + suma, -11.0, 14.50));
		box.setScale(glm::vec3(3.0, 6.00, 6.0));
		box.render();

		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.63 + suma, -11.0, 10.55));
		box.setScale(glm::vec3(3.0, 6.00, 1.9));
		box.render();

		//Mueble madera izq
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.6 + suma, -11.0, 1.00));
		box.setScale(glm::vec3(3.0, 6.00, 6.0));
		box.render();

		//Estufa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.6 + suma, -11.0, 6.800));//.25
		box.setScale(glm::vec3(3.0, 6.00, 5.6));
		box9.render();


		//--Arriba
		//Mueble madera  der
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.63 + suma, -2.5, 13.50));
		box.setScale(glm::vec3(3.0, 3.00, 8.9));
		box.render();

		//Mueble madera  izq
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.6 + suma, -2.5, 1.00));
		box.setScale(glm::vec3(3.0, 3.00, 6.0));
		box.render();

		//Arriba Estufa mueble
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(22.6 + suma, -2.25, 6.800));//.25
		box.setScale(glm::vec3(3.0, 2.50, 5.6));
		box.render();
		//Arriba Estufa grasa
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(22.1 + suma, -3.75, 6.800));//.25
		box.setScale(glm::vec3(4.0, 0.50, 5.6));
		box.render();

		//Mueble madera  izqcosas  
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(14.5 + suma, -11.0, 16.00));
		box.setScale(glm::vec3(7.0, 6.00, 3.0));
		box.render();

		//Mueble madera izqcosas  arriba
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(14.5 + suma, -2.5, 16.00));
		box.setScale(glm::vec3(7.0, 3.00, 3.0));
		box.render();

		//microondaas
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box.setPosition(glm::vec3(16.5 + suma, -7.25, 16.750));
		box.setScale(glm::vec3(3.0, 1.50, 1.5));
		box.render();

		//mesa
		glBindTexture(GL_TEXTURE_2D, textureID67);
		box.setPosition(glm::vec3(10.5 + suma, -9.00, 6.750));
		box.setScale(glm::vec3(3.5, 0.20, 10.50));
		box.render();


		/*Acaba Cuarto 1*/
		/*Compu afuera de cuartos */
		//  pared separa cochera 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(24.5 + suma, -8.5, -9.5));
		box9.setScale(glm::vec3(1.0, 15.0, 56.0));
		box9.render();
		//  pared separa sala y pared cochera
		glBindTexture(GL_TEXTURE_2D, textureID6);
		box9.setPosition(glm::vec3(10.5 + suma, -8.5, -25.5));
		box9.setScale(glm::vec3(1.0, 15.0, 22.0));
		box9.render();

		//---- Entrada del coche Cochera -----//
		glBindTexture(GL_TEXTURE_2D, textureID5);
		box8.setPosition(glm::vec3(34.75 + suma, -14.00, -55.8));
		box8.setScale(glm::vec3(21.5, 0.1, 38.0));
		box8.render();
		//---- Entrada del coche Calle -----//
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(34.75 + suma, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(13.25 + suma, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-8.25 + suma, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-29.75 + suma, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();
		glBindTexture(GL_TEXTURE_2D, textureID3);
		box8.setPosition(glm::vec3(-51.25 + suma, -14.00, -86.0));
		box8.setScale(glm::vec3(21.5, 0.1, 22.5));
		box8.render();

		//Puertas Abajo 

		//Puerta oficina
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(10.5 + suma, -8.5, -11.50));
		box.setScale(glm::vec3(1.0, 11.0, 6.0));
		box.render();

		//Puerta entrada
		glBindTexture(GL_TEXTURE_2D, textureID22);
		box.setPosition(glm::vec3(10.5 + suma, -8.5, 32.5));
		box.setScale(glm::vec3(1, 11.0, 6.0));
		box.render();

		//Helicopter
		//glm::mat4 Helicopter = glm::mat4(1.0);
		//Helicopter = glm::translate(Helicopter, glm::vec3(-35.0, -14.0, -30.0));
		//Helicopter = glm::scale(Helicopter, glm::vec3(3.0, 3.0, 3.00));
		//Helicopter = glm::rotate(Helicopter, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.00));
		ModelPlanta.render(Helicopter);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

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

		///----------------------------------------------------------------------Bob

		/*

		sphereLamp.render(lightModelmatrix);

		model = glm::translate(model, glm::vec3(0, 0, dz));
		model = glm::rotate(model, rot0, glm::vec3(0, 1, 0));
		//box1.enableWireMode();
		//Descomentar
		// Usamos la textura ID 1
		glBindTexture(GL_TEXTURE_2D, textureID1);
		box1.render(glm::scale(model, glm::vec3(1.0, 1.0, 0.1)));
		//Descomentar
		// No utilizar ninguna textura
		glBindTexture(GL_TEXTURE_2D, 0);

		// Articulacion 1
		glm::mat4 j1 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		j1 = glm::rotate(j1, rot1, glm::vec3(0, 0, 1));
		j1 = glm::rotate(j1, rot2, glm::vec3(0, 1, 0));
		//sphere1.enableWireMode();
		sphere1.render(glm::scale(j1, glm::vec3(0.1, 0.1, 0.1)));

		// Hueso 1
		glm::mat4 l1 = glm::translate(j1, glm::vec3(0.25f, 0.0, 0.0));
		l1 = glm::rotate(l1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l1, glm::vec3(0.1, 0.5, 0.1)));

		// Articulacion 2
		glm::mat4 j2 = glm::translate(j1, glm::vec3(0.5, 0.0f, 0.0f));
		j2 = glm::rotate(j2, rot3, glm::vec3(0.0, 0.0, 1.0));
		j2 = glm::rotate(j2, rot4, glm::vec3(1.0, 0.0, 0.0));
		//sphere1.enableWireMode();
		sphere1.render(glm::scale(j2, glm::vec3(0.1, 0.1, 0.1)));

		// Hueso 2
		glm::mat4 l2 = glm::translate(j2, glm::vec3(0.25, 0.0, 0.0));
		l2 = glm::rotate(l2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(l2, glm::vec3(0.1, 0.5, 0.1)));




		//Articulacion3
		glm::mat4 j3 = glm::translate(j2, glm::vec3(0.45, 0.2523, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(j3, glm::vec3(0.1, 0.1, 0.1)));
		j3 = glm::rotate(j3, d11, glm::vec3(1, 0, 0));///1
		//j3 = glm::rotate(j3, d11, glm::vec3(0, 1, 0));///1

		//dedo 1
		glm::mat4 d1 = glm::translate(j3, glm::vec3(0.1, 0.1, 0.0f));
		d1 = glm::rotate(d1, glm::radians(120.0f), glm::vec3(0, 0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(d1, glm::vec3(0.04, 0.2, 0.1)));


		//dedo 2
		glm::mat4 d2 = glm::translate(j3, glm::vec3(0.12, 0.05, 0.0f));
		d2 = glm::rotate(d2, glm::radians(100.0f), glm::vec3(0, 0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(d2, glm::vec3(0.04, 0.2, 0.1)));

		//dedo 3
		glm::mat4 d3 = glm::translate(j3, glm::vec3(0.14, 0.00, 0.0f));
		d3 = glm::rotate(d3, glm::radians(80.0f), glm::vec3(0, 0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(d3, glm::vec3(0.04, 0.2, 0.1)));

		//dedo 4
		glm::mat4 d4 = glm::translate(j3, glm::vec3(0.16, -0.05, 0.0f));
		d4 = glm::rotate(d4, glm::radians(60.0f), glm::vec3(0, 0, 1.0));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(d4, glm::vec3(0.04, 0.2, 0.1)));


		//Pupila
		glm::mat4 pupila1 = glm::translate(model, glm::vec3(0.25, 0.25, 0.065f));
		//sphere1.enableWireMode();
		sphere1.render(glm::scale(pupila1, glm::vec3(0.1, 0.1, 0.1)));
		//Pupila 2
		glm::mat4 pupila2 = glm::translate(model, glm::vec3(-0.25, 0.25, 0.065f));
		//sphere1.enableWireMode();
		sphere1.render(glm::scale(pupila2, glm::vec3(0.1, 0.1, 0.1)));

		//articulacion Izq
		glm::mat4 a1 = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(a1, glm::vec3(0.1, 0.1, 0.1)));
		a1 = glm::rotate(a1, rot3, glm::vec3(0, 0, 1));///1
		a1 = glm::rotate(a1, rot3, glm::vec3(0, 1, 0));///1

		//hueso Izq
		glm::mat4 h1 = glm::translate(a1, glm::vec3(-0.25f, 0.0f, 0.0f));
		h1 = glm::rotate(h1, glm::radians(90.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(h1, glm::vec3(0.1, 0.5, 0.1)));

		//articulacion2 Izq
		glm::mat4 a2 = glm::translate(a1, glm::vec3(-0.5f, 0.0f, 0.0f));
		sphere1.enableWireMode();
		sphere1.render(glm::scale(a2, glm::vec3(0.1, 0.1, 0.1)));
		a2 = glm::rotate(a2, rot4, glm::vec3(1, 0, 0));///1
		a2 = glm::rotate(a2, rot4, glm::vec3(0, 1, 0));///1

		//hueso2 Izq
		glm::mat4 h2 = glm::translate(a2, glm::vec3(-0.215, -0.1223, 0.0f));
		h2 = glm::rotate(h2, glm::radians(120.0f), glm::vec3(0, 0, 1.0));
		cylinder1.enableWireMode();
		cylinder1.render(glm::scale(h2, glm::vec3(0.1, 0.5, 0.1)));

		//Pantalon
		glm::mat4 p = glm::translate(model, glm::vec3(0.0f, -0.625f, 0.0f));
		//box2.enableWireMode();
		box2.render(glm::scale(p, glm::vec3(1.0, 0.25, 0.1)));

		glm::mat4 p2 = glm::translate(p, glm::vec3(-0.25f, -0.25f, 0.0f));
		//cylinder2.enableWireMode();
		cylinder2.render(glm::scale(p2, glm::vec3(0.25, 0.25, 0.1)));

		glm::mat4 p3 = glm::translate(p, glm::vec3(0.25f, -0.25f, 0.0f));
		//cylinder2.enableWireMode();
		cylinder2.render(glm::scale(p3, glm::vec3(0.25, 0.25, 0.1)));

		//Pies

		glm::mat4 pie = glm::translate(p2, glm::vec3(0.0f, -0.375f, 0.0f));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(pie, glm::vec3(0.1, 0.5, 0.1)));

		glm::mat4 pie2 = glm::translate(p3, glm::vec3(0.0f, -0.375f, 0.0f));
		//cylinder1.enableWireMode();
		cylinder1.render(glm::scale(pie2, glm::vec3(0.1, 0.5, 0.1)));


		//Pie IZQ
		glm::mat4 p6 = glm::translate(pie, glm::vec3(0.0f, -0.275f, 0.15f));
		p6 = glm::rotate(p6, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		cylinder2.enableWireMode();
		cylinder2.render(glm::scale(p6, glm::vec3(0.1f, 0.25f, 0.1f)));

		//Pie DER
		glm::mat4 p7 = glm::translate(pie2, glm::vec3(0.0f, -0.275f, 0.15f));
		p7 = glm::rotate(p7, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		cylinder2.enableWireMode();
		cylinder2.render(glm::scale(p7, glm::vec3(0.1f, 0.25f, 0.1f)));


		//BOCA
		glm::mat4 b = glm::translate(model, glm::vec3(0.0f, -0.30f, 0.05f));
		//box3.enableWireMode();
		box3.render(glm::scale(b, glm::vec3(0.50, 0.15, 0.1)));


		/////////////////////////////////////////////////////////////////////////////////////////
		//apartir de aqui se modelara a R2D2

		glm::mat4 torso = glm::translate(modelR2D2, glm::vec3(5.0f, 0.0f, 0.0f));
		torso = glm::rotate(torso, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//torsoR2D2.enableWireMode();
		torsoR2D2.render(glm::scale(torso, glm::vec3(1.0f, 1.0f, 1.0f)));

		glm::mat4 cabeza = glm::translate(torso, glm::vec3(0.0f, 0.5f, 0.0f));
		//cabezaR2D2.enableWireMode();
		cabezaR2D2.render(glm::scale(cabeza, glm::vec3(1.0f, 1.0f, 1.0f)));

		//
		///ojo
		glm::mat4 oj1 = glm::translate(cabeza, glm::vec3(0.0f, 0.2f, 0.4f));
		//sphere1.enableWireMode();
		sphere3.render(glm::scale(oj1, glm::vec3(0.15, 0.15, 0.15)));

		glm::mat4 articulacioDerecha = glm::translate(torso, glm::vec3(0.55f, 0.35f, 0.0f));
		//articulacionR2D2.enableWireMode();
		articulacionR2D2.render(glm::scale(articulacioDerecha, glm::vec3(0.15f, 0.15f, 0.15f)));
		articulacioDerecha = glm::rotate(articulacioDerecha, rota1, glm::vec3(0, 0, 1));///1
		articulacioDerecha = glm::rotate(articulacioDerecha, rota1, glm::vec3(0, 1, 0));///1

		glm::mat4 brazoDer = glm::translate(articulacioDerecha, glm::vec3(0.05f, -0.4f, -0.13f));
		brazoDer = glm::rotate(brazoDer, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//brazoR2D2.enableWireMode();
		brazoR2D2.render(glm::scale(brazoDer, glm::vec3(0.15f, 1.0f, 0.1f)));

		glm::mat4 munecaDerecha = glm::translate(brazoDer, glm::vec3(0.0f, -0.5f, 0.0f));;
		//articulacionR2D2.enableWireMode();
		articulacionR2D2.render(glm::scale(munecaDerecha, glm::vec3(0.15f, 0.15f, 0.15f)));

		glm::mat4 pataDerecha = glm::translate(munecaDerecha, glm::vec3(0.0f, -0.1f, 0.0f));
		//pieR2D2.enableWireMode();
		pieR2D2.render(glm::scale(pataDerecha, glm::vec3(0.2f, 0.2f, 0.2f)));

		glm::mat4 articulacioIzquierda = glm::translate(torso, glm::vec3(-0.55f, 0.35f, 0.0f));
		//articulacionR2D2.enableWireMode();
		articulacionR2D2.render(glm::scale(articulacioIzquierda, glm::vec3(0.15f, 0.15f, 0.15f)));
		articulacioIzquierda = glm::rotate(articulacioIzquierda, rota2, glm::vec3(1, 0, 0));///1

		glm::mat4 brazoIzq = glm::translate(articulacioIzquierda, glm::vec3(-0.05f, -0.4f, -0.13f));
		brazoIzq = glm::rotate(brazoIzq, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//brazoR2D2.enableWireMode();
		brazoR2D2.render(glm::scale(brazoIzq, glm::vec3(0.15f, 1.0f, 0.1f)));

		glm::mat4 munecaIzquierda = glm::translate(brazoIzq, glm::vec3(0.0f, -0.5f, 0.0f));;
		articulacionR2D2.enableWireMode();
		articulacionR2D2.render(glm::scale(munecaIzquierda, glm::vec3(0.15f, 0.15f, 0.15f)));

		glm::mat4 pataIzquierda = glm::translate(munecaIzquierda, glm::vec3(0.0f, -0.1f, 0.0f));
		//pieR2D2.enableWireMode();
		pieR2D2.render(glm::scale(pataIzquierda, glm::vec3(0.2f, 0.2f, 0.2f)));

		glm::mat4 coxis = glm::translate(torso, glm::vec3(0.0f, -0.15f, 0.0f));
		//cabezaR2D2.enableWireMode();
		cabezaR2D2.render(glm::scale(coxis, glm::vec3(1.0f, 1.0f, 1.0f)));

		glm::mat4 artiulacionCentral = glm::translate(coxis, glm::vec3(0.0f, -0.55f, 0.0f));
		//articulacionR2D2.enableWireMode();
		articulacionR2D2.render(glm::scale(artiulacionCentral, glm::vec3(0.15f, 0.15f, 0.15f)));

		glm::mat4 pataCentral = glm::translate(artiulacionCentral, glm::vec3(0.0f, -0.1f, 0.0f));
		pataCentral = glm::rotate(pataCentral, glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//pieR2D2.enableWireMode();
		pieR2D2.render(glm::scale(pataCentral, glm::vec3(0.2f, 0.2f, 0.2f)));
		/////////////////////////////////////////////////////////////////////////////////////////

				shader.turnOff();
		*/

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
		sofa = glm::scale(sofa, glm::vec3(1.8000, 2.000,2.00));
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
		mesa2 = glm::translate(mesa2, glm::vec3(-4.0 + suma , -14.0, 10.0));
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

		
		//ModelTrineo
		glm::mat4 trineo = glm::mat4(1.0);
		trineo = glm::translate(trineo, glm::vec3(-12.0, 6.0, -44.0));
		trineo = glm::scale(trineo, glm::vec3(0.02, 0.02, 0.020));
		ModelTrineo.render(trineo);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelPinoNavidad
		glm::mat4 pino = glm::mat4(1.0);
		pino = glm::translate(pino, glm::vec3(-11.0, -14.0, 30.0));
		pino = glm::scale(pino, glm::vec3(3.0, 3.0, 3.00));
		ModelPinoNavidad.render(pino);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelPinoNavidad
		glm::mat4 estrella = glm::mat4(1.0);
		estrella = glm::translate(estrella, glm::vec3(-11.0, -14.0, 30.0));
		estrella = glm::scale(estrella, glm::vec3(3.0, 3.0, 3.00));
		ModelEstrella.render(estrella);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);

		//ModelPinoNavidad
		glm::mat4 esfera = glm::mat4(1.0);
		esfera = glm::translate(esfera, glm::vec3(-11.0, -14.0, 30.0));
		esfera = glm::scale(esfera, glm::vec3(3.0, 3.0, 3.00));
		ModelEsfera.render(esfera);
		//Forze to enable the unit texture 0 always ............ IMPORTANT
		glActiveTexture(GL_TEXTURE0);
		
		
			

		/*

		;
		;
		ModelBaston;
		ModelCaballito;
		ModelCalceta;
		ModelChimenea;
		ModelPinoNavidad;
		ModelHat;
		ModelDinosaur;
		ModelNochebuena;
		ModelRegaloUno;
		ModelRegaloDos;
		ModelRosa;
		ModelSpiderman;
		ModelTren;
		ModelTrineo;

		ModelPrueba;

		*/
		/*Fin de objetos Navidad*/

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
			std::cout << "Land the plane" << std::endl;
			std::cout << offsetAircraftAdvanceII << std::endl;
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
			std::cout << "Fly" << std::endl;
			std::cout << offsetAircraftAdvanceII << std::endl;
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

			std::cout << "Stop" << std::endl;
			std::cout << rotHelHelYStop << std::endl;
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
		switch (state) {
		case 0:
			std::cout << "Advance" << std::endl;
			std::cout << offsetAircraftAdvance << std::endl;
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
			modelMatrixEclipse = glm::translate(modelMatrixEclipse, glm::vec3(0.0, 0.0, 0.025));
			modelMatrixEclipse = glm::rotate(modelMatrixEclipse, glm::radians(0.5f), glm::vec3(0, 1, 0));
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

		/////////////////////////////

		glfwSwapBuffers(window);
	}
}

int main(int argc, char** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
