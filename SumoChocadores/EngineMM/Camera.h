#ifndef CAMERA_H
#define CAMERA_H
#include "Game.h"
#include "Composite.h"
class IMPORTEXPORT Camera:
	public Composite
{
private:
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _rot;
	D3DXMATRIX projection;
	D3DXMATRIX view;
	int radian;
	int ancho;
	int alto;
	float dismin;
	float dismax;
	D3DXMATRIX _projection_view;
public:
	Camera();
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	~Camera();
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos() const;
	D3DXVECTOR3 GetRot() const;
	D3DXMATRIX GetViewMatrix() const;
	void update();
	void setSize(int _radian, int _ancho, int _alto, float _dismin, float _dismax);
	D3DMATRIX getProjection() const;
	vector<D3DXPLANE> BuildViewFrustum(); //Tiene que tener acceso al Projection. Pide Projection y View.
};
#endif 
