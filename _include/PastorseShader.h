#ifndef INCLUDE_PASTORSESHADER_H_
#define INCLUDE_PASTORSESHADER_H_ 1

#include "PastorseTypes.h"

struct Shader{
  char8* vertexSource;
  char8* fragmentSource;
};

static Shader getBasicShader(){
  Shader shader;

  shader.vertexSource = 
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
    "}\n";

  shader.fragmentSource = 
    "#version 330 core\n"
    "uniform vec3 color_;"
    "out vec4 FragColor;"
    "void main()\n"
    "{\n"
    "FragColor = vec4(color_,1.0);\n"
    "}\n";

  return shader;
}

static Shader getTextureShader(){
  Shader shader;

  shader.vertexSource = 
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "layout(location = 2) in vec2 text_coords;\n"
    "out vec2 textCoords;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "out vec2 coord_text; \n"
    "out vec3 norm; \n"
    "out vec3 direction; \n"
    "void main()\n"
    "{\n"
    "textCoords = text_coords;\n"
    "gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
    "}\n";

  shader.fragmentSource = 
    "#version 330 core\n"
    "in vec2 textCoords;\n"
    "uniform sampler2D texture_;\n"
	"uniform vec3 color_;"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
	"color = vec4(texture2D(texture_,textCoords));\n"

    "}\n";
  return shader;
}

static Shader getRenderToTextureShader(){
  Shader shader;

  shader.vertexSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"

    "layout(location = 2) in vec2 text_coords;\n"
    "out vec2 textcoords;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0f);\n"
    "textcoords = text_coords.xy * -1.0f;\n"
    "}\n";

  shader.fragmentSource =
    "#version 330 core\n"
    "in vec2 textcoords;\n"
    "out vec4 FragColor;"
    "uniform sampler2D texture_;\n"
    "void main()\n"
    "{\n"
    "FragColor = texture2D(texture_, textcoords);\n"
    "}\n";

  return shader;
}

static Shader getRenderToTextureShaderRed(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"

		"layout(location = 2) in vec2 text_coords;\n"
		"out vec2 textcoords;\n"
		"void main()\n"
		"{\n"
			"gl_Position = vec4(position, 1.0f);\n"
			"textcoords = text_coords.xy * -1.0f;\n"
		"}\n";

	shader.fragmentSource =
		"#version 330 core\n"
		"in vec2 textcoords;\n"
		"uniform sampler2D texture_;\n"
		"out vec4 FragColor;\n"

		"void main()\n"
		"{\n"
		"vec4 top = texture2D(texture_, vec2(textcoords.x, textcoords.y + 1.0 / 300.0));\n"
		"vec4 bottom = texture2D(texture_, vec2(textcoords.x, textcoords.y - 1.0 / 300.0));\n"
		"vec4 left = texture2D(texture_, vec2(textcoords.x - 1.0 / 300.0, textcoords.y));\n"
		"vec4 right = texture2D(texture_, vec2(textcoords.x + 1.0 / 300.0, textcoords.y));\n"
		"vec4 topLeft = texture2D(texture_, vec2(textcoords.x - 1.0 / 300.0, textcoords.y + 1.0 / 300.0));\n"
		"vec4 topRight = texture2D(texture_, vec2(textcoords.x + 1.0 / 300.0, textcoords.y + 1.0 / 300.0));\n"
		"vec4 bottomLeft  = texture2D(texture_, vec2(textcoords.x - 1.0 / 300.0, textcoords.y - 1.0 / 300.0));\n"
		"vec4 bottomRight = texture2D(texture_, vec2(textcoords.x + 1.0 / 300.0, textcoords.y - 1.0 / 300.0));\n"

		"vec4 sx = -topLeft - 2 * left - bottomLeft + topRight + 2 * right + bottomRight;\n"
		"vec4 sy = -topLeft - 2 * top - topRight + bottomLeft + 2 * bottom + bottomRight;\n"
		"vec4 sobel = sqrt(sx * sx + sy * sy);\n"

		"if(sobel.r<0.1 &&sobel.g<0.1 &&sobel.b<0.1)\n"
		"{\n"
			"sobel = texture2D(texture_, textcoords);\n"
		"}\n"
			"FragColor =  sobel;\n"
		"}\n";

	return shader;
}

static Shader getRenderToTextureShaderGreen(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"out vec2 textcoords;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position, 1.0f);\n"
		"textcoords = text_coords.xy * -1.0f;\n"
		"}\n";

	shader.fragmentSource =
		"#version 330 core\n"
		"in vec2 textcoords;\n"
		"out vec4 FragColor;"
		"uniform sampler2D texture_;\n"
		"void main()\n"
		"{\n"

		"vec3 blur = vec3(0.0);\n"
		"vec2 texel_size = 1.0 / textureSize(texture_,0);\n"
		"int x,y;\n"
		"for(x = -3; x <= 3; ++x)\n"
		"{\n"
		  "for(y = -3; y <= 3; ++y)\n"
		  "{\n"
			  "blur += texture2D(texture_,textcoords + vec2(x,y) * texel_size).xyz;\n"
		  "}\n"
		"}\n"
		"blur = blur/49;\n"

		"FragColor = vec4(blur,1.0);\n"
		"}\n";

	return shader;
}

static Shader getLightBasicShader(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"

		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"uniform mat4 cam_model;\n"
		"uniform mat4 object_model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec2 texture_coords;\n"
		"out vec3 light_normal; \n"
		"out vec3 frag_position; \n"
		"void main()\n"
		"{\n"
			"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
			"texture_coords = text_coords;\n"
			"frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
			"light_normal = mat3(transpose(inverse(cam_model * object_model))) * normal;\n"
		"}\n";

  shader.fragmentSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "in vec2 texture_coords;\n"
    "in vec3 light_normal; \n "
    "in vec3 frag_position;\n"
    "uniform sampler2D texture_;\n"
    "uniform vec3 color_;"
    "uniform vec3 light_pos;"
    "uniform vec3 light_color;"
    "uniform vec3 camera_position;"
    "void main()\n"
    "{\n"
    "float ambient_intensity = 0.5f;\n"
    "vec3 ambient_light = ambient_intensity * vec3(1.0f,0.5f,0.5f);\n"

    "vec3 normal = normalize(light_normal);\n"
    "vec3 light_direction = normalize(vec3(100.0f,0.0f,0.0f) - frag_position); //normalize(light_pos - frag_position);\n"
    "float diff = max(dot(normal, light_direction), 0.0);\n"
    "vec3 diffuse_light = diff * vec3(1.0f,0.5f,0.5f); //light_color;\n"

    "float specular_intensity = 0.7f;\n"
    "vec3 view_direction = normalize(camera_position - frag_position);\n"
    "vec3 reflection_direction = reflect(-light_direction, normal);\n"
    "float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);\n"
    "vec3 specular_light = specular_intensity * spec * vec3(1.0f,0.5f,0.5f); //light_color;\n"

    "vec3 result = (ambient_light + diffuse_light + specular_light) * color_;\n"
		"color = vec4(result, 1.0);\n"

	"}\n";

	return shader;
}

static Shader getLightTextureShader(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"

		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"uniform mat4 cam_model;\n"
		"uniform mat4 object_model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec2 texture_coords;\n"
		"out vec3 light_normal; \n"
		"out vec3 frag_position; \n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
		"texture_coords = text_coords;\n"
		"frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
		"light_normal = mat3(transpose(inverse(object_model))) * normal;\n"
		"}\n";

	shader.fragmentSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"in vec2 texture_coords;\n"
		"in vec3 light_normal; \n "
		"in vec3 frag_position;\n"
		"uniform sampler2D texture_;\n"
		"uniform vec3 color_;"
		"uniform vec3 light_pos;"
		"uniform vec3 light_color;"
		"uniform vec3 camera_position;"
		"void main()\n"
		"{\n"
		"float ambient_intensity = 0.5f;\n"
		"vec3 ambient_light = ambient_intensity * vec3(1.0f,0.5f,0.5f); //light_color;\n"

		"vec3 normal = normalize(light_normal);\n"
		"vec3 light_direction = normalize(vec3(100.0f,0.0f,0.0f) - frag_position); //normalize(light_pos - frag_position);\n"
		"float diff = max(dot(normal, light_direction), 0.0);\n"
		"vec3 diffuse_light = diff * vec3(1.0f,0.5f,0.5f); //light_color;\n"

		"float specular_intensity = 0.7f;\n"
		"vec3 view_direction = normalize(camera_position - frag_position);\n"
		"vec3 reflection_direction = reflect(-light_direction, normal);\n"
		"float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);\n"
		"vec3 specular_light = specular_intensity * spec * vec3(1.0f,0.5f,0.5f); //light_color;\n"

		"vec3 result = (ambient_light + diffuse_light + specular_light) * color_;\n"
		"color = vec4(result, 1.0) * texture2D(texture_,texture_coords);\n"

		"}\n";

	return shader;
}



static Shader getLightDirectionalTextureShader(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"

		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"uniform mat4 cam_model;\n"
		"uniform mat4 object_model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec2 texture_coords;\n"
		"out vec3 light_normal; \n"
		"out vec3 frag_position; \n"
		"void main()\n"
		"{\n"
		"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
		"texture_coords = text_coords;\n"
		"frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
		"light_normal = mat3(transpose(inverse(object_model))) * normal;\n"
		"}\n";

	shader.fragmentSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"in vec2 texture_coords;\n"
		"in vec3 light_normal; \n "
		"in vec3 frag_position;\n"
		"uniform sampler2D texture_;\n"
		"uniform vec3 color_;"
		"uniform vec3 directional_light_direction;"
		"uniform vec3 directional_light_color;"
		"uniform vec3 camera_position;"
		"void main()\n"
		"{\n"
		"vec3 ambient_light = 0.5 * directional_light_color;\n"

		"vec3 normal = normalize(light_normal);\n"
		"vec3 light_dir = normalize(-directional_light_direction);\n"
		"float diff = max(dot(normal, light_dir), 0.0);\n"
		"vec3 diffuse_light = diff * directional_light_color;\n"

		"vec3 view_direction = normalize(camera_position - frag_position);\n"
		"vec3 reflection_direction = reflect(-light_dir, normal);\n"
		"float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);\n"
		"vec3 specular_light = 0.7 * spec * directional_light_color;\n"

		"vec4 texture_color = texture2D(texture_,texture_coords.xy);"

		"vec3 result = (ambient_light + diffuse_light + specular_light);\n"
		"color = vec4(result * texture_color.xyz, 1.0);\n"

		"}\n";

	return shader;
}

static Shader getPointLightTextureShader(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"

		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"uniform mat4 cam_model;\n"
		"uniform mat4 object_model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec2 texture_coords;\n"
		"out vec3 light_normal; \n"
		"out vec3 frag_position; \n"
		"void main()\n"
		"{\n"
			"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
			"texture_coords = text_coords;\n"
			"frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
			"light_normal = mat3(transpose(inverse(object_model))) * normal;\n"
		"}\n";

	shader.fragmentSource =
		"#version 330 core\n"
		"out vec4 color;\n"
		"in vec2 texture_coords;\n"
		"in vec3 light_normal; \n "
		"in vec3 frag_position;\n"
		"uniform sampler2D texture_;\n"
		"uniform vec3 point_light_position;"
		"uniform vec3 point_light_color;"
		"uniform vec3 camera_position;"
		"uniform float point_light_constant;"
		"uniform float point_light_linear;"
		"uniform float point_light_quadratic;"
		"void main()\n"
		"{\n"
			"vec3 ambient_light = 0.5f * point_light_color;\n"

			"vec3 normal = normalize(light_normal);\n"
			"vec3 light_direction = normalize(point_light_position - frag_position);\n"
			"float diff = max(dot(normal, light_direction), 0.0);\n"
			"vec3 diffuse_light = 0.5f * diff * point_light_color;\n"

			"vec3 view_direction = normalize(camera_position - frag_position);\n"
			"vec3 reflection_direction = reflect(-light_direction, normal);\n"
			"float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);\n"
			"vec3 specular_light = spec * point_light_color;\n"

			"float distance = length(point_light_position - frag_position);\n"
			"float attenuation = 1.0f / (point_light_constant + point_light_linear * distance + point_light_quadratic * (distance * distance));\n"

			"ambient_light *= attenuation;\n"
			"diffuse_light *= attenuation;\n"
			"specular_light *= attenuation;\n"

			"vec4 texture_color = texture2D(texture_,texture_coords.xy);"

			"vec3 result = (ambient_light + diffuse_light + specular_light);\n"
			"color = vec4( result + texture_color.xyz, 1.0);\n"

		"}\n";

	return shader;
}

static Shader getLightDirectionalTestTextureShader(){
 Shader shader;

  shader.vertexSource =
    "#version 330 core\n"

    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "layout(location = 2) in vec2 text_coords;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 shadow_view;\n"
    "uniform mat4 shadow_model;\n"
    "uniform mat4 shadow_projection;\n"
    "out vec2 texture_coords;\n"
    "out vec3 light_normal; \n"
    "out vec3 frag_position; \n"
    "out vec4 shadow_frag_position; \n"
    "void main()\n"
    "{\n"
		"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
		"texture_coords = text_coords;\n"
		"frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
		"light_normal = mat3(transpose(inverse(object_model))) * normal;\n"
		"shadow_frag_position = shadow_projection * shadow_view * shadow_model * object_model * vec4(position, 1.0f);"
    "}\n";

  shader.fragmentSource =
	  "#version 330 core\n"
	  "out vec4 color;\n"
	  "in vec2 texture_coords;\n"
	  "in vec3 light_normal; \n "
	  "in vec3 frag_position;\n"
	  "in vec4 shadow_frag_position; \n"
	  "uniform sampler2D texture_shadow;\n"
	  "uniform sampler2D texture_;\n"
	  "uniform vec3 color_;"
	  "uniform vec3 directional_light_color;"
	  "uniform vec3 directional_light_direction;"
	  "uniform vec3 camera_position;"

	  //Function
	  "vec3 dirLight(vec3 direction, vec3 normal, vec3 color, vec3 view);\n"
	  "float shadow(vec4 frag_position, sampler2D texture);\n"

	  "void main()\n"
	  "{\n"

	  "vec3 norm = normalize(light_normal);\n"
	  "vec3 view_direction = normalize(camera_position - frag_position);\n"

	  "vec3 result = dirLight(directional_light_direction, norm, directional_light_color, view_direction);\n"
	  "float shadow = shadow(shadow_frag_position, texture_shadow);\n"
	
		"vec4 texture_color = texture2D(texture_,texture_coords);"

		"color = vec4(result * texture_color.xyz * shadow ,1.0) ;\n"   
    "}\n"

	/// Directional
   "vec3 dirLight(vec3 direction, vec3 normal, vec3 color, vec3 view)\n"
	"{\n"
		"vec3 direction_light = normalize(-direction);\n"
	
		"float diff = max(dot(normalize(normal), direction_light), 0.0);\n"
	
		"vec3 reflection_direction = reflect(-direction_light, normalize(normal));\n"
		"float spec = pow(max(dot(view, reflection_direction), 0.0), 32);\n"

		"vec3 ambient_light = 0.5 * color;\n"
		"vec3 diffuse_light =  0.2 * diff * color;\n"
		"vec3 specular_light = spec * color;\n"

		"return (ambient_light +  diffuse_light + specular_light);\n"
	"}\n"

  /// Shadow
  "float shadow(vec4 frag_position, sampler2D texture)\n"
	  "{\n"
		"vec3 shadow_value = (frag_position / frag_position.w).xyz * 0.5 + vec3(0.5);\n"
		"float shadow = 0.0;\n"
		"vec2 texel_size = 1.0 / textureSize(texture,0);\n"
		"int x,y;\n"
		"for(x = -1; x <= 1; ++x)\n"
		"{\n"
		  "for(y = -1; y <= 1; ++y)\n"
		  "{\n"
		  "if(shadow_value.z < texture2D(texture,shadow_value.xy + vec2(x,y) * texel_size).r + 0.007)\n"
			"{\n"
			  "shadow +=1,0;\n"
			"}\n"
		  "}\n"
		"}\n"
		"shadow = shadow/9 + 0.2;\n"
		"return shadow;\n"
	  "}\n";

  return shader;
}

static Shader getRenderPositionShader(){
  Shader shader;

  shader.vertexSource =
    "#version 330 core\n"

    "layout(location = 0) in vec3 position;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "out vec3 frag_position; \n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
    "frag_position = vec3( projection * view  * cam_model * object_model * vec4(position, 1.0f));\n"
    "}\n";

  shader.fragmentSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "in vec3 frag_position;\n"
    "void main()\n"
    "{\n"
    "color = vec4(vec3(frag_position.z),1.0);\n"

    "}\n";

  return shader;
}

static Shader getLightSpotLightTextureShader(){
	Shader shader;

	shader.vertexSource =
		"#version 330 core\n"

		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 normal;\n"
		"layout(location = 2) in vec2 text_coords;\n"
		"uniform mat4 cam_model;\n"
		"uniform mat4 object_model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"uniform mat4 shadow_view;\n"
		"uniform mat4 shadow_model;\n"
		"uniform mat4 shadow_projection;\n"
		"out vec2 texture_coords;\n"
		"out vec3 light_normal; \n"
		"out vec3 frag_position; \n"
		"out vec4 shadow_frag_position; \n"
		"void main()\n"
		"{\n"
			"gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
			"texture_coords = text_coords;\n"
			"frag_position = vec3(object_model * vec4(position, 1.0f));\n"
			"light_normal = normal;\n"
		"}\n";

  shader.fragmentSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "in vec2 texture_coords;\n"
    "in vec3 light_normal; \n "
    "in vec3 frag_position;\n"
    "uniform sampler2D texture_;\n"
    "uniform vec3 spot_light_direction;\n"
    "uniform vec3 spot_light_color;\n"
	"uniform vec3 spot_light_position;"
    "uniform vec3 camera_position;"
    "uniform float spot_light_inner_angle;"
    "uniform float spot_light_outer_angle;"
    "uniform float spot_light_constant;"
    "uniform float spot_light_linear;"
    "uniform float spot_light_quadratic;"

    "void main()\n"
    "{\n"
		"vec3 ambient_light = 0.2 * spot_light_color;\n"

		"vec3 normal_light_dir = normalize(-spot_light_direction);\n"

		"vec3 normal = normalize(light_normal);\n"
		"vec3 light_dir = normalize(spot_light_position - frag_position);\n"
		"float diff = max(dot(normal, normal_light_dir),0.0);\n"
		"vec3 diffuse_light = diff * spot_light_color;\n"

		"vec3 view_direction = normalize(camera_position - frag_position);\n"
		"vec3 reflection_direction = reflect(normal_light_dir, normal);\n"
		"float spec = pow(max(dot(view_direction, reflection_direction), 0.0), 32);\n"
		"vec3 specular_light = 0.7 * spec * spot_light_color;\n"

		"float theta = dot(light_dir, normal_light_dir);\n"
		"float epsilon = (spot_light_inner_angle - spot_light_outer_angle); \n"
		"float intensity = clamp((theta - spot_light_outer_angle) / epsilon, 0.0, 1.0); \n"
		 
		"diffuse_light *= intensity; \n"
		"specular_light *= intensity; \n"

		"float distance = length(spot_light_position - frag_position);\n"
		"float attenuation = 1.0f / (spot_light_constant + spot_light_linear * distance + spot_light_quadratic * (distance * distance));\n"
		
		"ambient_light *= attenuation; \n"
		"diffuse_light *= attenuation; \n"
		"specular_light *= attenuation; \n"

		"vec4 texture_color = texture2D(texture_,texture_coords.xy);"
	
		"color = vec4((diffuse_light + specular_light + ambient_light) * texture_color.xyz ,1.0) ;\n"

		//"color = texture2D(texture_,texture_coords);\n"
		//"color = texture2D(texture_,shadow_value.xy); \n"

	"}\n";

	return shader;
}

static Shader getLightSpotLightTestTextureShader(){
  Shader shader;

  shader.vertexSource =
    "#version 330 core\n"

    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "layout(location = 2) in vec2 text_coords;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 shadow_view;\n"
    "uniform mat4 shadow_model;\n"
    "uniform mat4 shadow_projection;\n"
    "out vec2 texture_coords;\n"
    "out vec3 light_normal; \n"
    "out vec3 frag_position; \n"
    "out vec4 shadow_frag_position; \n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
    "texture_coords = text_coords;\n"
    "frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
    "light_normal = normal;\n"
    "shadow_frag_position = shadow_projection * shadow_view * shadow_model * object_model * vec4(position, 1.0f);"
    "}\n";

  shader.fragmentSource =
    "#version 330 core\n"
    "out vec4 color;\n"
    "in vec2 texture_coords;\n"
    "in vec3 light_normal; \n "
    "in vec3 frag_position;\n"
    "in vec4 shadow_frag_position; \n"
    "uniform sampler2D texture_shadow;\n"
    "uniform sampler2D texture_;\n"
    "uniform vec3 light_direction2;"
    "uniform vec3 spot_light_color;"
    "uniform vec3 camera_position;"
	"uniform float spot_light_inner_angle;"
	"uniform float spot_light_outer_angle;"
	"uniform float spot_light_constant;"
	"uniform float spot_light_linear;"
	"uniform float spot_light_quadratic;"
	"uniform vec3 spot_light_position;"

	/// SpotLight
   "vec3 spotLight(vec3 view)\n"
	"{\n"
		"vec3 direction_light = normalize(-light_direction2);\n"
		"vec3 direction_position_light = normalize(light_pos - frag_position);\n"

		"float diff = max(dot(normalize(light_normal), direction_light), 0.0);\n"
	
		"vec3 reflection_direction = reflect(-direction_light, normalize(light_normal));\n"
		"float spec = pow(max(dot(view, reflection_direction), 0.0), 32);\n"

		"vec3 ambient_light = 0.2 * light_color;\n"
		"vec3 diffuse_light = 0.5 * diff * light_color;\n"
		"vec3 specular_light = 0.7 * spec * light_color;\n"

		"float theta = dot(direction_position_light, direction_light);\n"
		"float epsilon = (light_inner_angle - spot_light_outer_angle); \n"
		"float intensity = clamp((theta - spot_light_outer_angle) / epsilon, 0.0, 1.0); \n"

		"diffuse_light *= intensity; \n"
		"specular_light *= intensity; \n"

		"float distance = length(light_pos - frag_position);\n"
		"float attenuation = 1.0f / (light_constant + light_linear * distance + light_quadratic * (distance * distance));\n"

		"diffuse_light *= attenuation; \n"
		"specular_light *= attenuation; \n"

		"return (ambient_light + diffuse_light + specular_light);\n"
	"}\n"

	 /// Shadow
  "float shadow(vec4 frag_position, sampler2D texture)\n"
	  "{\n"
		"vec3 shadow_value = (frag_position / frag_position.w).xyz * 0.5 + vec3(0.5);\n"
		"float shadow = 0.0;\n"
		"vec2 texel_size = 1.0 / textureSize(texture,0);\n"
		"int x,y;\n"
		"for(x = -1; x <= 1; ++x)\n"
		"{\n"
		  "for(y = -1; y <= 1; ++y)\n"
		  "{\n"
		  "if(shadow_value.z < texture2D(texture,shadow_value.xy + vec2(x,y) * texel_size).r + 0.007)\n"
			"{\n"
			  "shadow +=1.0;\n"
			"}\n"
		  "}\n"
		"}\n"
		"shadow = shadow/9 + 0.2;\n"
		"return shadow;\n"
	  "}\n"


  "void main()\n"
	  "{\n"

	  "vec3 view_direction = normalize(camera_position - frag_position);\n"
	  "float shadow = shadow(shadow_frag_position,texture_shadow) ;\n"

		"vec3 result = spotLight(view_direction);\n"
		"color = vec4(result * shadow,1.0) ;\n"
     
    "}\n";

  return shader;


}

static Shader getLightSpotDirectionalLightTestTextureShader(){
     Shader shader;

  shader.vertexSource =
    "#version 330 core\n"

    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "layout(location = 2) in vec2 text_coords;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 shadow_view;\n"
    "uniform mat4 shadow_model;\n"
    "uniform mat4 shadow_projection;\n"
	"uniform mat4 shadow_view2;\n"
	"uniform mat4 shadow_model2;\n"
	"uniform mat4 shadow_projection2;\n"
    "out vec2 texture_coords;\n"
    "out vec3 light_normal; \n"
    "out vec3 frag_position; \n"
    "out vec4 shadow_frag_position; \n"
	"out vec4 shadow_frag_position2; \n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
    "texture_coords = text_coords;\n"
    "frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
    "light_normal = normal;\n"
    "shadow_frag_position = shadow_projection * shadow_view * shadow_model * object_model * vec4(position, 1.0f);"
	"shadow_frag_position2 = shadow_projection2 * shadow_view2 * shadow_model2 * object_model * vec4(position, 1.0f);"
    "}\n";

  shader.fragmentSource =
	  "#version 330 core\n"
	  "out vec4 color;\n"
	  "in vec2 texture_coords;\n"
	  "in vec3 light_normal; \n "
	  "in vec3 frag_position;\n"
	  "in vec4 shadow_frag_position; \n"
	  "in vec4 shadow_frag_position2; \n"
	  "uniform sampler2D texture_shadow;\n"
	  "uniform sampler2D texture_shadow_2;\n"
	  "uniform sampler2D texture_;\n"

	  "uniform vec3 directional_light_direction;"
	  "uniform vec3 directional_light_color;"
	  "uniform vec3 camera_position;"

	  "uniform float spot_light_inner_angle;"
	  "uniform float spot_light_outer_angle;"
	  "uniform float spot_light_constant;"
	  "uniform float spot_light_linear;"
	  "uniform float spot_light_quadratic;"
	  "uniform vec3 spot_light_position;"
	  "uniform vec3 spot_light_direction;"
	  "uniform vec3 spot_light_color;"

	  /// Directional
   "vec3 dirLight(vec3 direction, vec3 normal, vec3 color, vec3 view)\n"
	"{\n"
		"vec3 direction_light = normalize(-direction);\n"
	
		"float diff = max(dot(normalize(normal), direction_light), 0.0);\n"
	
		"vec3 reflection_direction = reflect(-direction_light, normalize(normal));\n"
		"float spec = pow(max(dot(view, reflection_direction), 0.0), 32);\n"

		"vec3 ambient_light = 0.2 * color;\n"
		"vec3 diffuse_light = 0.5 * diff * color;\n"
		"vec3 specular_light = 0.7 * spec * color;\n"

		"return (ambient_light + diffuse_light + specular_light);\n"
	"}\n"

  /// Shadow
  "float shadow(vec4 frag_position, sampler2D texture)\n"
	  "{\n"
		"vec3 shadow_value = (frag_position / frag_position.w).xyz * 0.5 + vec3(0.5);\n"
		"float shadow = 0.0;\n"
		"vec2 texel_size = 1.0 / textureSize(texture,0);\n"
		"int x,y;\n"
		"for(x = -1; x <= 1; ++x)\n"
		"{\n"
		  "for(y = -1; y <= 1; ++y)\n"
		  "{\n"
		  "if(shadow_value.z < texture2D(texture,shadow_value.xy + vec2(x,y) * texel_size).r + 0.007)\n"
			"{\n"
			  "shadow +=1.0;\n"
			"}\n"
		  "}\n"
		"}\n"
		"shadow = shadow/9 + 0.2;\n"
		"return shadow;\n"
	  "}\n"

	   /// Shadow
  "float shadow2(vec4 frag_position, sampler2D texture)\n"
	  "{\n"
		"vec3 shadow_value = (frag_position / frag_position.w).xyz * 0.5 + vec3(0.5);\n"
		"float shadow = 0.0;\n"
		"vec2 texel_size = 1.0 / textureSize(texture,0);\n"
		"int x,y;\n"
		"for(x = -1; x <= 1; ++x)\n"
		"{\n"
		  "for(y = -1; y <= 1; ++y)\n"
		  "{\n"
		  "if(shadow_value.z < texture2D(texture,shadow_value.xy + vec2(x,y) * texel_size).r + 0.009)\n"
			"{\n"
			  "shadow +=1.0;\n"
			"}\n"
		  "}\n"
		"}\n"
		"shadow = shadow/9 + 0.2;\n"
		"return shadow;\n"
	  "}\n"

	  /// Spotlight
	   "vec3 spotLight(vec3 view)\n"
	"{\n"
		"vec3 direction_light = normalize(-spot_light_direction);\n"
		"vec3 direction_position_light = normalize(spot_light_position - frag_position);\n"

		"float diff = max(dot(normalize(light_normal), direction_light), 0.0);\n"
	
		"vec3 reflection_direction = reflect(-direction_light, normalize(light_normal));\n"
		"float spec = pow(max(dot(view, reflection_direction), 0.0), 32);\n"

		//"vec3 ambient_light = 0.2 * light_color;\n"
		"vec3 diffuse_light = 0.5 * diff * spot_light_color;\n"
		"vec3 specular_light = 0.7 * spec * spot_light_color;\n"

		"float theta = dot(direction_position_light, direction_light);\n"
		"float epsilon = (spot_light_inner_angle - spot_light_outer_angle); \n"
		"float intensity = clamp((theta - spot_light_outer_angle) / epsilon, 0.0, 1.0); \n"

		"diffuse_light *= intensity; \n"
		"specular_light *= intensity; \n"

		"float distance = length(spot_light_position - frag_position);\n"
		"float attenuation = 1.0f / (spot_light_constant + spot_light_linear * distance + spot_light_quadratic * (distance * distance));\n"

		"diffuse_light *= attenuation; \n"
		"specular_light *= attenuation; \n"

		"return (diffuse_light + specular_light);\n"
	"}\n"

	  "void main()\n"
	  "{\n"

	  "vec3 norm = normalize(light_normal);\n"
	  "vec3 view_direction = normalize(camera_position - frag_position);\n"

	  "vec3 ambient_light = 0.2 * directional_light_color;\n"
	  "vec3 spot = spotLight(view_direction);\n"
	  "vec3 dir= dirLight(directional_light_direction, norm, directional_light_color, view_direction);\n" 

	  "float shadow_v = shadow(shadow_frag_position, texture_shadow);\n"
	  "float shadow_v2 = shadow2(shadow_frag_position2, texture_shadow_2);\n"

	  "vec3 final_result = ambient_light + spot*shadow_v2 + dir * shadow_v;\n"
	
	  "vec4 texture_color = texture2D(texture_,texture_coords.xy);"

	  "color = vec4(final_result * texture_color.xyz ,1.0) ;\n"   
    "}\n";

  return shader;

}

static Shader getLightThreeSpotOneDirectionalLightTextureShader(){
      Shader shader;

  shader.vertexSource =
    "#version 330 core\n"

    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 normal;\n"
    "layout(location = 2) in vec2 text_coords;\n"
    "uniform mat4 cam_model;\n"
    "uniform mat4 object_model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 shadow_view;\n"
    "uniform mat4 shadow_model;\n"
    "uniform mat4 shadow_projection;\n"
    "out vec2 texture_coords;\n"
    "out vec3 light_normal; \n"
    "out vec3 frag_position; \n"
    "out vec4 shadow_frag_position; \n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view  * cam_model * object_model * vec4(position, 1.0f);\n"
    "texture_coords = text_coords;\n"
    "frag_position = vec3(cam_model * object_model * vec4(position, 1.0f));\n"
    "light_normal = normal;\n"
    "}\n";

  shader.fragmentSource =
	  "#version 330 core\n"
	  "out vec4 color;\n"
	  "in vec2 texture_coords;\n"
	  "in vec3 light_normal; \n "
	  "in vec3 frag_position;\n"
	  "in vec4 shadow_frag_position; \n"
	  "uniform sampler2D texture_;\n"
	  "uniform vec3 camera_position;"

	  "uniform vec3 spot_light_direction;"
	  "uniform vec3 spot_light_color;"
	  "uniform float spot_light_inner_angle;"
	  "uniform float spot_light_outer_angle;"
	  "uniform float spot_light_constant;"
	  "uniform float spot_light_linear;"
	  "uniform float spot_light_quadratic;"
	  "uniform vec3 spot_light_position;"

	  "uniform vec3 spot_light_direction_2;"
	  "uniform vec3 spot_light_color_2;"
	  "uniform float spot_light_inner_angle_2;"
	  "uniform float spot_light_outer_angle_2;"
	  "uniform float spot_light_constant_2;"
	  "uniform float spot_light_linear_2;"
	  "uniform float spot_light_quadratic_2;"
	  "uniform vec3 spot_light_position_2;"

	  "uniform vec3 spot_light_direction_3;"
	  "uniform vec3 spot_light_color_3;"
	  "uniform float spot_light_inner_angle_3;"
	  "uniform float spot_light_outer_angle_3;"
	  "uniform float spot_light_constant_3;"
	  "uniform float spot_light_linear_3;"
	  "uniform float spot_light_quadratic_3;"
	  "uniform vec3 spot_light_position_3;"

	  /// SpotLight
	  "vec3 spotLight(vec3 view, vec3 direction, vec3 position, vec3 color, float inner, float outer, float quadratic, float linear, float constant)\n"
	  "{\n"
	  "vec3 direction_light = normalize(-direction);\n"
	  "vec3 direction_position_light = normalize(position - frag_position);\n"

	  "float diff = max(dot(normalize(light_normal), direction_light), 0.0);\n"

	  "vec3 reflection_direction = reflect(-direction_light, normalize(light_normal));\n"
	  "float spec = pow(max(dot(view, reflection_direction), 0.0), 32);\n"

	  "vec3 ambient_light = 0.2 * color;\n"
	  "vec3 diffuse_light = 0.5 * diff * color;\n"
	  "vec3 specular_light = 0.7 * spec * color;\n"

	  "float theta = dot(direction_position_light, direction_light);\n"
	  "float epsilon = (inner - outer); \n"
	  "float intensity = clamp((theta - outer) / epsilon, 0.0, 1.0); \n"

	  "diffuse_light *= intensity; \n"
	  "specular_light *= intensity; \n"

	  "float distance = length(position - frag_position);\n"
	  "float attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));\n"

	    "ambient_light *= attenuation;\n"
		"diffuse_light *= attenuation; \n"
		"specular_light *= attenuation; \n"

		"return (ambient_light + diffuse_light + specular_light);\n"
	"}\n"

  "void main()\n"
	  "{\n"

	  "vec3 view_direction = normalize(camera_position - frag_position);\n"

		"vec3 result = spotLight(view_direction, spot_light_direction, spot_light_position, spot_light_color, spot_light_inner_angle, spot_light_outer_angle, spot_light_quadratic, spot_light_linear, spot_light_constant);\n"
		"result += spotLight(view_direction, spot_light_direction_2, spot_light_position_2, spot_light_color_2, spot_light_inner_angle_2, spot_light_outer_angle_2, spot_light_quadratic_2, spot_light_linear_2, spot_light_constant_2);\n"
		"result += spotLight(view_direction, spot_light_direction_3, spot_light_position_3, spot_light_color_3, spot_light_inner_angle_3, spot_light_outer_angle_3, spot_light_quadratic_3, spot_light_linear_3, spot_light_constant_3);\n"

		"vec4 texture_color = texture2D(texture_,texture_coords.xy);"

		"color = vec4(result * texture_color.xyz ,1.0) ;\n"
     
    "}\n";

  return shader;

}

#endif