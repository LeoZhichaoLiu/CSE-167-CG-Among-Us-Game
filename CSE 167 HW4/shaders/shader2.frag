#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
//in float sampleExtraOutput;
in vec3 outputColor;
in vec3 FragPos;  //The position of fragment.
in vec3 Normal;   // The color of that fragment.
in vec2 TexCoords;

uniform vec3 color;

// Material values:
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;

//Point light value: light_color/position.
uniform vec3 light_color;
uniform vec3 LightPos;

uniform sampler2D ourTexture;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 fragColor;

void main()
{
       vec3 light = vec3 (0, 0, 0);
      
       vec3 Ambient = light_color * ambient;
      
    
       vec3 normal = normalize(Normal);
       vec3 light_direction = normalize (LightPos - FragPos);
       vec3 Diffuse =  light_color * (max (dot(normal, light_direction), 0)) * diffuse;
    
       vec3 view_direction = normalize (vec3(0,0,1) - FragPos);
       vec3 reflect_direction = reflect(-light_direction, normal);
       float specular_factor = pow(max (dot(view_direction, reflect_direction), 0), shininess);
       vec3 Specular = light_color * specular_factor * specular;
    
       // Attenuation
       float distance = length(LightPos - FragPos);
       float attenuation = 1.0f / (0.09 * distance);
    
       light = attenuation * (Ambient + Specular);
       
       fragColor = vec4(light, 1) + texture(ourTexture, TexCoords);
       //fragColor = texture(ourTexture, TexCoords) * vec4(light, 1);
        
}
