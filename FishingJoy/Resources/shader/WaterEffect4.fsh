varying vec4 v_fragmentColor;  
varying vec2 v_texCoord;  
   
uniform sampler2D u_normalMap;  
 
 
vec3 waveNormal(vec2 p) {  
    vec3 normal = texture2D(u_normalMap, p).xyz;  
    normal = -1.0 + normal * 2.0;  
    return normalize(normal);  
}  
   
void main() {  
    float timeFactor = 0.1;  
    float offsetFactor = 0.5;  
    float refractionFactor = 0.7;  
       
    // simple UV animation  
    vec3 normal = waveNormal(v_texCoord + vec2(CC_Time.y * timeFactor, CC_Time.x * timeFactor));  
       
    // simple calculate refraction UV offset  
    vec2 p = -1 + 2 * v_texCoord;  
    vec3 eyePos = vec3(0, 0, 10); //�۾�λ�� λ�����ĵ����Ϸ�  
    vec3 inVec = normalize(vec3(p, 0) - eyePos);  
    vec3 refractVec = refract(inVec, normal, refractionFactor);  //�����������������ߣ�����ϵ��������������
    vec2 v_texCoordN = v_texCoord;
    v_texCoordN += refractVec.xy * offsetFactor;    
    //v_texCoordN.x -= CC_Time.y*timeFactor *0.6; //�ƶ�ˮ����ͼ����ѡ
       
    gl_FragColor = texture2D(CC_Texture0, v_texCoordN);  
}  