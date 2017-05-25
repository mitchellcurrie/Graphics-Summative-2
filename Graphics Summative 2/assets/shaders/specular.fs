#version 430 core

in vec2 TexCoord;
in vec3 OutNormVec;
in vec3 OutFragPosition;

out vec4 color;

uniform sampler2D Texture;
uniform float ambientStrength, specularStrength;

// Ambient and diffuse light
uniform vec3 
lightColor,
objectColor,
lightPosition,
viewPosition;


//vec3 ApplyLight(int lightType);

void main() {

    for (int x = 0; x < 2; x++)
    { 
        float attenuation = 1.0f;

//        if (x == 1)
//        {
//            lightColor = vec(1.0f, 0.0f, 0.0f);
//        }

        // Ambient light
        vec3 ambientValue = ambientStrength * lightColor;

        // Diffuse light
        vec3 normal = normalize(OutNormVec);
        vec3 lightDir = normalize(lightPosition - OutFragPosition);

        float difference = max(dot(normal, lightDir), 0.0f);
        vec3 diffuseValue = difference * lightColor;
     
        // Specular light
        vec3 viewDir = normalize(viewPosition - OutFragPosition);
        vec3 reflectionDir = reflect(-lightDir, normal);
        //float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32);
    
        // Gouraud Shader
        vec3 halfVector = normalize(lightDir + viewDir);

        float spec = pow(max(dot(normal, halfVector), 0.0f), 32);
        vec3 specularValue = spec * lightColor * specularStrength;


        ////// NEW ////

        if (x == 1) // spotlight
        {
            vec3 coneDirection = vec3(1.0f, 0.0f, 0.0f);
            float coneAngle = 10.0f; // degrees

            float lightToSurfaceAngle = degrees(acos(dot(lightDir, normalize(coneDirection))));

            if(lightToSurfaceAngle > coneAngle)
            {
                attenuation = 0.0f;
            }
        }

        ////// END NEW //////

        // Final values
        vec3 finalObjectLight = (ambientValue + diffuseValue + specularValue) * objectColor * attenuation;

        color += texture(Texture, TexCoord) * vec4(finalObjectLight,  1.0f);
    }

 //   color = texture(Texture, TexCoord) * vec4(finalObjectLight,  1.0f);

 //   return finalObjectLight;
}