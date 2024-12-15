#version 330 core
out vec3 outColor;

in vec3 normal;  
in vec3 pos;
in vec3 color;
  
uniform vec3 lightColor;
uniform vec3 lightPos; 
uniform vec3 viewPos; 

void main(){
    float ambientStrength = 0.05;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 lightDir = normalize(lightPos - pos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(pos - viewPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    outColor = (ambient + diffuse + specular) * color;
}