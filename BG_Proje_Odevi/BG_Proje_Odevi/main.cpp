#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<string>
#include<map>
#include <iostream>
#include <time.h>   
#include<glm/glm.hpp>
#include<vector>
std::vector<glm::vec3> vertices;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 inPos;\n"				// [x y z]; (vertex - köþe koord. bilgileri)
"uniform vec3 uMove;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(inPos+uMove, 1.0);\n"				// [x y z 1.0];
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"	fragColor = vec4(1.0, 0.5, 0.4, 1.0);\n"				// [x y z 1.0];
"}\0";
float boyut;
float konum;
void YonAta(int* yon, float* position);
void PozisyonAta(int* yon, float* position);
//float haraketMiktari = 0.08;
int yonBir = 4;
int yonIki = 4;
int yonUc = 3;

bool sekilBirOnay = false;
bool sekilIkiOnay = false;
bool sekilUcOnay = false;

//Kayhan hocanýn çalýmaþlarýndan yararlandým.
void buildCircle(float radius, int vertexCount)
{
	float angle = 360.0f / vertexCount;

	int triangleCount = vertexCount - 2;

	std::vector<glm::vec3>   tempVertices;

	for (int i = 0; i < vertexCount; i++)
	{
		float newAngle = angle * i;

		float x = radius * cos(glm::radians(newAngle));

		float y = radius * sin(glm::radians(newAngle));

		float z = 0.0f;

		tempVertices.push_back(glm::vec3(x, y, z));

	}


	for (int i = 0; i < triangleCount; i++)
	{
		vertices.push_back(tempVertices[0]);
		vertices.push_back(tempVertices[i + 1]);
		vertices.push_back(tempVertices[i + 2]);
	}

}
bool CarpismaaVarmi(float* positionBir, float* positionIki) {
	if((positionBir[0] + boyut* 2.0f > positionIki[0] && positionBir[0] < positionIki[0] + boyut* 2.0f) &&
		(positionBir[1] + boyut* 2.0f > positionIki[1] && positionBir[1] < positionIki[1] + boyut* 2.0f))
	{
		std::cout << "Carpisma tespit edildi!\n";
		return true;
	}
	return false;
}
void PozisyonAta(int* yon, float* position)
{
	switch (*yon) {
	case 1:
		position[1] += 0.001f;
		break;
	case 2:
		position[0] += 0.001f;
		position[1] += 0.001f;
		break;
	case 3:
		position[0] += 0.001f;
		break;
	case 4:
		position[0] += 0.001f;
		position[1] -= 0.001f;
		break;
	case 5:
		position[1] -= 0.001f;
		break;
	case 6:
		position[0] -= 0.001f;
		position[1] -= 0.001f;
		break;
	case 7:
		position[0] -= 0.001f;
		break;
	case 8:
		position[0] -= 0.001f;
		position[1] += 0.001f;
		break;
	}
	YonAta(yon, position);
}
void YonAta(int* yon,float* position) {

	if (position[0] + boyut > 1) {
		if (*yon == 2)
			*yon = 8;
		if (*yon == 3)
			*yon = 7;
		if (*yon == 4)
			*yon = 6;
	}
	if (position[0] - boyut < -1) {
		if (*yon == 8)
			*yon = 2;
		if (*yon == 7)
			*yon = 3;
		if (*yon == 6)
			*yon = 4;
	}
	if (position[1] + boyut > 1) {
		if (*yon == 8)
			*yon = 6;
		if (*yon == 1)
			*yon = 5;
		if (*yon == 2)
			*yon = 4;
	}
	if (position[1] - boyut < -1) {
		if (*yon == 6)
			*yon = 8;
		if (*yon == 5)
			*yon = 1;
		if (*yon == 4)
			*yon = 2;
	}
}
void SekilBelirle() {
	int gecici = rand() % 3;

	if (gecici == 0) {
		sekilBirOnay = true;
		gecici = rand() % 2;
		if (gecici == 0) {
			sekilIkiOnay = true;
		}
		else
		{
			sekilUcOnay = true;
		}
	}
	else if (gecici == 1) {
		sekilIkiOnay = true;
		gecici = rand() % 2;
		if (gecici == 0) {
			sekilBirOnay = true;
		}
		else
		{
			sekilUcOnay = true;
		}
	}
	else if (gecici == 2) {
		sekilUcOnay = true;
		gecici = rand() % 2;
		if (gecici == 0) {
			sekilBirOnay = true;
		}
		else
		{
			sekilIkiOnay = true;
		}
	}

}
void RastgeleSayilariAta() {
	yonBir = (rand() % 8) + 1;
	yonIki = (rand() % 8) + 1;
	yonUc = (rand() % 8) + 1;
	boyut = (float)rand() / RAND_MAX;
	while (boyut < 0.05f || boyut > 0.17f) {
		boyut = (float)rand() / RAND_MAX;
	}
}
float RastgeleKonum() {
	float konum2 = (float)rand() / RAND_MAX;
	while (konum < 0.12f || boyut > 0.17f) {
		konum = (float)rand() / RAND_MAX;
	}
	if (konum2 < 0.0975)
		konum2 = -konum2;
	return konum2;
}
int main()
{
	
	srand((unsigned)time(NULL));
	RastgeleSayilariAta();
	SekilBelirle();

	float positionBir[] = {
	RastgeleKonum(),RastgeleKonum(), 0.0f
	};
	float positionIki[] = {
	RastgeleKonum(), RastgeleKonum(), 0.0f
	};
	float positionUc[] = {
	RastgeleKonum(), RastgeleKonum(), 0.0f
	};
	float verticesUcgen[] = {
		 0.0f,   boyut, 0.0f,			// üçgenin birinci köþe noktasý
		 boyut, -boyut, 0.0f,			// üçgenin ikinci köþe noktasý
		-boyut, -boyut, 0.0f,			// üçgenin üçüncü köþe noktasý
	};
	float verticesKare[] = {
	-boyut,  boyut, 0.0f,
	-boyut, -boyut, 0.0f,
	 boyut, -boyut, 0.0f,

	-boyut,  boyut, 0.0f,
	 boyut, -boyut, 0.0f,
	 boyut,  boyut, 0.0f,

	};
	if (!glfwInit())
	{
		std::cout << "GLFW kütüphanesi baþlatýlamadý!...\n";
		return -1;
	}

	GLFWwindow* pencere = glfwCreateWindow(800, 600, "Omer Faruk Simsek - G181210371 - OpenGL Uygulama", NULL, NULL);

	glfwWindowHint(GLFW_SAMPLES, 4);					// 4x antialising(kenar yumuþatma)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);		// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// içerik tanýmlanýyor
	glfwMakeContextCurrent(pencere);

	// GLAD loader baþlatýlýyor
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "OpenGL içeriði oluþturulamadý!...";
		return -1;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader);
	glLinkProgram(shaderProgram2);
	buildCircle(boyut, 32);
	unsigned int shaderProgram3 = glCreateProgram();
	glAttachShader(shaderProgram3, vertexShader);
	glAttachShader(shaderProgram3, fragmentShader);
	glLinkProgram(shaderProgram3);
	std::map<std::string, unsigned int>  m_UniformVars;
	m_UniformVars["uMove"] = glGetUniformLocation(shaderProgram, "uMove");
	m_UniformVars["uMove"] = glGetUniformLocation(shaderProgram2, "uMove");
	m_UniformVars["uMove"] = glGetUniformLocation(shaderProgram3, "uMove");

	unsigned int VBO;
	unsigned int VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesKare), verticesKare, GL_STATIC_DRAW);

	//glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	// pencere kapatýlýncaya kadar döner
	while (!glfwWindowShouldClose(pencere))
	{
		// çizim alaný

		// varsayýlan renk belirleniyor
		glClearColor(0.6, 0.6, 0.6, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		
		
		if (sekilBirOnay) {
			PozisyonAta(&yonBir, positionBir);
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticesKare), verticesKare, GL_STATIC_DRAW);

			glUniform3f(m_UniformVars["uMove"], positionBir[0], positionBir[1], 0.0f);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (sekilIkiOnay) {
			PozisyonAta(&yonIki, positionIki);
			glUseProgram(shaderProgram2);
			glBindVertexArray(VAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUcgen), verticesUcgen, GL_STATIC_DRAW);

			glUniform3f(m_UniformVars["uMove"], positionIki[0], positionIki[1], 0.0f);

			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		if (sekilUcOnay) {
			PozisyonAta(&yonUc, positionUc);
			glUseProgram(shaderProgram2);
			glBindVertexArray(VAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* vertices.size(), &vertices[0], GL_STATIC_DRAW);

			glUniform3f(m_UniformVars["uMove"], positionUc[0], positionUc[1], 0.0f);

			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		}

		if (sekilBirOnay && sekilIkiOnay) {
			if (CarpismaaVarmi(positionBir, positionIki)) {
				glfwDestroyWindow(pencere);
				glfwTerminate();
			}
		}
		else if (sekilBirOnay && sekilUcOnay) {
			if (CarpismaaVarmi(positionBir, positionUc)) {
				glfwDestroyWindow(pencere);
				glfwTerminate();
			}
		}
		else if (sekilIkiOnay && sekilUcOnay) {
			if (CarpismaaVarmi(positionIki, positionUc)) {
				glfwDestroyWindow(pencere);
				glfwTerminate();
			}
		}


		// çizim tamponlarýný yer deðiþtir
		glfwSwapBuffers(pencere);
		glfwPollEvents();

	}



	return 0;
}