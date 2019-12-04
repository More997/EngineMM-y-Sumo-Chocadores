#include "stdafx.h"
#include "Component.h"
#include "Composite.h"
#include "MeshRenderer.h"

Component::Component() : translationVector(0, 0, 0), scaleXData(1), scaleYData(1), scaleZData(1), scaleVector(1,1,1)
{
	D3DXMatrixIdentity(&_scale);
	D3DXMatrixIdentity(&_translation);
	D3DXMatrixIdentity(&_rotation);		//Inicializo las matrices escala, rotacion y traslacion como matriz indentidad. Para que no arranque con basura.

	//defineTransformationMatrix();
}
Component::~Component()
{
}
void Component::SetModelPosition(float translationX, float translationY, float translationZ)
{
	translationVector.x = translationX;
	translationVector.y = translationY;
	translationVector.z = translationZ;
	D3DXMatrixTranslation(&_translation, translationX, translationY, translationZ); //Constructor de la matriz de traslacion. Ahorra muchos pasos y riesgos.
	//defineTransformationMatrix();
}

void Component::SetModelScale(float scaleX, float scaleY, float scaleZ)
{
	scaleXData = scaleX;
	scaleYData = scaleY;
	scaleZData = scaleZ;
	scaleVector.x = scaleX;
	scaleVector.y = scaleY;
	scaleVector.z = scaleZ;
	D3DXMatrixScaling(&_scale, scaleXData, scaleYData, scaleZData); //Constructor de la matriz de escala. Ahorra muchos pasos y riesgos.
}
void Component::SetModelRotation(float rotationX, float rotationY, float rotationZ)
{
	rotationXData = rotationX;
	rotationYData = rotationY;
	rotationZData = rotationZ;

	rotationVector.x = rotationX;
	rotationVector.y = rotationY;
	rotationVector.z = rotationZ;

	D3DXMATRIX testRotX;
	D3DXMATRIX testRotY;
	D3DXMATRIX testRotZ;

	D3DXMatrixRotationX(&testRotX, D3DXToRadian(rotationVector.x));
	D3DXMatrixRotationY(&testRotY, D3DXToRadian(rotationVector.y));
	D3DXMatrixRotationZ(&testRotZ, D3DXToRadian(rotationVector.z));

	_rotation = testRotX * testRotY * testRotZ;


}
void Component::SetModelRotationX(float rotationX)
{
	rotationXData = rotationX;
	D3DXMatrixRotationX(&_rotation, rotationXData);
}
void Component::SetModelRotationY(float rotationY)
{
	rotationYData = rotationY;
	D3DXMatrixRotationY(&_rotation, rotationYData);
}
D3DXVECTOR3 Component::GetPosition() const
{
	return translationVector;
}
D3DXVECTOR3 * Component::GetPositionByReference()
{
	return &translationVector;
}
D3DXVECTOR3 Component::GetScale() const
{
	return scaleVector;
}
D3DXVECTOR3 Component::GetRotation() const
{
	return rotationVector;
}
void Component::SetVectorPosition(D3DXVECTOR3 theVector)
{
	SetModelPosition(theVector.x, theVector.y, theVector.z);
}
float Component::GetScaleX() const
{
	return scaleVector.x;
}
float Component::GetScaleY() const
{
	return scaleYData;
}
float Component::GetScaleZ() const
{
	return scaleZData;
}
D3DXMATRIX Component::GetRotationMatrix()
{
	return _rotation;
}
float Component::GetRotationX() const
{
	return rotationXData;
}
float Component::GetRotationY() const
{
	return rotationYData;
}
float Component::GetRotationZ() const
{
	return rotationZData;
}
void Component::defineTransformationMatrix()
{
	//TODO: En caso de ser un meshrenderer tomar el BB original del mesh y aplicarle la transformacion
	//TODO: En caso de ser un composite agregarle a lo anterior (si es valido) los BB de los hijos
	//COMPONENT NO TIENE QUE TRABAJAR EN BOUNDING BOX
	//HACER UN FOR QUE MULTIPLIQUE/SUME LOS BB.




	D3DXQUATERNION rotationQuaternion;
	D3DXMatrixTransformation(&_transformationMatrix, NULL, NULL, &scaleVector, NULL, D3DXQuaternionRotationYawPitchRoll(&rotationQuaternion, D3DXToRadian(rotationVector.x),
		D3DXToRadian(rotationVector.y), D3DXToRadian(rotationVector.z)), &translationVector);

//	std::cout << "relleno" << std::endl;

/*
	D3DXMatrixIdentity(&_transformationMatrix);

	//Forma de DirectX
	D3DXMatrixMultiply(&_transformationMatrix, &_translation, &_transformationMatrix);
	D3DXMatrixMultiply(&_transformationMatrix, &_rotation, &_transformationMatrix);
	D3DXMatrixMultiply(&_transformationMatrix, &_scale, &_transformationMatrix);

	
	*/

	//Forma manual
	//_transformationMatrix = (_translation * _rotation * _scale);

	//bound = GetMeshBB()->Transform(translationVector, rotationVector, scaleVector); ESTO DEBERIA IR AL MESH RENDERER.
	if (parent != NULL)
	{
		_transformationMatrix = (parent->_transformationMatrix * _transformationMatrix);
	}
}
D3DXMATRIX Component::GetTransformationMatrix()
{
	//defineTransformationMatrix();
	return _transformationMatrix;  
}
void Component::Update()
{
}
void Component::Render()
{
	defineTransformationMatrix();
}

void Component::Move(float someX, float someY)
{
	x = someX;
	y = someY;
}
void Component::SetParent(Composite * parent)
{
	this->parent = parent; //Indico de quien es el componente, quien es el padre. En que objeto esta este componente.
}
Composite * Component::GetParent()
{
	return parent;
}
void Component::SetBoundingBox(BoundingBox _bound)
{
	bound = _bound;
	
}
BoundingBox Component::GetBoundingBox()
{
	return bound;
}