struct VS_INPUT
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : TEXCOORD2;
	float4 lightColor : TEXCOORD3;
};

float3 lightDirection;
float4 lightColor;
float4 ambientColor;
float4x4 MVPMatrix;
float4x4 rotMatrix;

sampler2D tex : register(s0);

float4 GetLight(float3 normal)
{
	float diffuse = dot(lightDirection, normal);
	return ambientColor + lightColor * diffuse;
}

VS_OUTPUT VS(VS_INPUT vertex)
{
	VS_OUTPUT fragment;
	fragment.position = mul(vertex.position, MVPMatrix);
	fragment.normal = mul(vertex.normal, rotMatrix);
	fragment.uv = vertex.uv;
	fragment.lightColor = GetLight(fragment.normal);
	return fragment;
}

float4 PS(VS_OUTPUT fragment) : COLOR
{
	float4 color = tex2D(tex, fragment.uv);
	return color * fragment.lightColor;
}

technique RedColor
{
	pass p0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}