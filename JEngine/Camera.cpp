#include "Camera.h"
#include "Matrix3.h"
#include "Window.h"
#include "Asset.h"
#include "Entity.h"
#include "glew.h"
#include "glfw3.h"

namespace JTL
{
	Matrix4 Camera::getView() {	return inverse(Matrix4::translate({pos})); }

	Matrix4 Camera::getOrtho()
	{
		float halfW, halfH;
		halfW = Window::instance().getWidth() / 2;
		halfH = Window::instance().getHeight() / 2;
		float quarterW = halfW / 2;
		float quarterH = halfH / 2;

#pragma region Space_Switch_Statement
		
		switch (space)
		{
		case JTL::Camera::FULL:
			return orthoProj(-halfW, halfW, -halfH, halfH, near ,far);
		
		case JTL::Camera::TOP_HALF:
			return orthoProj(-halfW, halfW, -quarterH, quarterH, near, far);
		
		case JTL::Camera::BOT_HALF:
			return orthoProj(-halfW, halfW, -quarterH, quarterH, near, far);
		
		case JTL::Camera::LFT_HALF:
			return orthoProj(-quarterW, quarterW, -halfH, halfH, near, far);

		case JTL::Camera::RGT_HALF:
			return orthoProj(-quarterW, quarterW, -halfH, halfH, near, far);

		case JTL::Camera::TL_CORNER:
			return orthoProj(-quarterW, quarterW, -quarterH, quarterH, near, far);

		case JTL::Camera::TR_CORNER:
			return orthoProj(-quarterW, quarterW, -quarterH, quarterH, near, far);

		case JTL::Camera::BL_CORNER:
			return orthoProj(-quarterW, quarterW, -quarterH, quarterH, near, far);

		case JTL::Camera::BR_CORNER:
			return orthoProj(-quarterW, quarterW, -quarterH, quarterH, near, far);

		case JTL::Camera::CENTER_SQUARE:
			return orthoProj(-quarterW, quarterW, -quarterH, quarterH, near, far);
		}

#pragma endregion

	}

	Matrix4 Camera::getPersp()
	{
		return perspProj(fov, Window::instance().getWidth() / Window::instance().getHeight(), far, near);
	}
	
	void Camera::update()
	{
		float w, h, halfW, halfH;
		w = Window::instance().getWidth();
		h = Window::instance().getHeight();
		halfW = w / 2;
		halfH = h / 2;

#pragma region Space_Switch_Statement

		switch (space)
		{
		case JTL::Camera::FULL:
			glViewport(0, 0, w, h);
			break;
		case JTL::Camera::TOP_HALF:
			glViewport(0, halfH, w, halfH);
			break;
		case JTL::Camera::BOT_HALF:
			glViewport(0, 0, w, halfH);
			break;
		case JTL::Camera::LFT_HALF:
			glViewport(0, 0, halfW, h);
			break;
		case JTL::Camera::RGT_HALF:
			glViewport(halfW, 0, halfW, h);
			break;
		case JTL::Camera::TL_CORNER:
			glViewport(0, halfH, halfW, halfH);
			break;
		case JTL::Camera::TR_CORNER:
			glViewport(halfW, halfH, halfW, halfH);
			break;
		case JTL::Camera::BL_CORNER:
			glViewport(0, 0, halfW, halfH);
			break;
		case JTL::Camera::BR_CORNER:
			glViewport(halfW, 0, halfW, halfH);
			break;
		case JTL::Camera::CENTER_SQUARE:
			float quarterW = halfW / 2;
			float quarterH = halfH / 2;
			glViewport(quarterW, quarterH, halfW, halfH);
			break;
		}

#pragma endregion

		for each (Entity e in Entity::getData())
		{
			if (e.sprite > -1)
			{
				if (e.transform > -1)
				{
					Asset::instance().drawTexture(e.sprite->assetName,
						e.sprite->shader,
						e.sprite->tint,
						e.sprite->frame,
						e.transform->getDrawMatrix(),
						getView(), getOrtho());
				}
				else
				{
					Asset::instance().drawTexture(e.sprite->assetName,
						e.sprite->shader,
						e.sprite->tint,
						e.sprite->frame,
						ID_MAT4,
						getView(), getOrtho());
				}
			}
		}
	}
}