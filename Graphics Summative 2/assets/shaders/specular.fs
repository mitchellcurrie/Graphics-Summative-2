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

// vec3 spotLightColor = vec3(0.0f, 1.0f, 0.0f);
vec3 lightColorToUse;

void main() {

//    for (int x = 0; x < 2; x++)
//    { 
        float attenuation = 1.0f;

 //       if (x == 0)       
             lightColorToUse = lightColor;
//        else
 //           lightColorToUse = spotLightColor;

        // Ambient light
        vec3 ambientValue = ambientStrength * lightColorToUse;

        // Diffuse light
        vec3 normal = normalize(OutNormVec);
        vec3 lightDir = normalize(lightPosition - OutFragPosition);

        float intensity = max(dot(normal, lightDir), 0.0f);
        vec3 diffuseValue = intensity * lightColorToUse;
     
        // Specular light
        vec3 viewDir = normalize(viewPosition - OutFragPosition);
        vec3 reflectionDir = reflect(-lightDir, normal);
        //float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32);
    
        // Gouraud Shader
        vec3 halfVector = normalize(lightDir + viewDir);

        float spec = pow(max(dot(normal, halfVector), 0.0f), 32);
        vec3 specularValue = spec * lightColorToUse * specularStrength;


//        // Spotlight
//        if (x == 1) 
//        {
//            vec3 coneDirection = vec3(1.0f, 0.0f, 0.0f);
//            float coneAngle = 12.0f; // degrees
//
//            float lightToSurfaceAngle = degrees(acos(dot(lightDir, normalize(coneDirection))));
//
//            if(lightToSurfaceAngle > coneAngle)
//            {
//                attenuation = 0.0f;
//            }
//        }

        // Final values
        vec3 finalObjectLight = (ambientValue + diffuseValue + specularValue) * objectColor * attenuation;

        color += texture(Texture, TexCoord) * vec4(finalObjectLight,  1.0f);

        if (intensity > 0.95f)
		    color = vec4(0.5f, 0.5f, 1.0f, 1.0f);
	    else if (intensity > 0.5f)
		    color = vec4(0.3f, 0.3f, 0.6f, 1.0f);
	    else if (intensity > 0.25f)
		    color = vec4(0.2f ,0.2f ,0.4f ,1.0f);
	    else
		    color = vec4(0.1f, 0.1f, 0.2f, 1.0f);

//        if (intensity > 0.95f)
//		   color *= vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	    else if (intensity > 0.5f)
//		   color *= vec4(0.8f, 0.8f, 0.8f, 1.0f);
//	    else if (intensity > 0.25f)
//		   color *= vec4(0.4f, 0.4f, 0.4f, 1.0f);
//	    else
//		   color *= vec4(0.1f, 0.1f, 0.1f, 1.0f);






//    }  // end for loop

 //   color = texture(Texture, TexCoord) * vec4(finalObjectLight,  1.0f);

 //   return finalObjectLight;
}