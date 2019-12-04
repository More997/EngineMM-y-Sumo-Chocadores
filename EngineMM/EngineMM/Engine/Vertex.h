#pragma once
struct Vertex {
	FLOAT x, y, z;
	FLOAT nx, ny, nz; //Comentado, el engine es 2D. Descomentado, es 3D. El FVF tambien influye.
	FLOAT tu, tv; //2D
	//FLOAT tu, tv; //3D
};