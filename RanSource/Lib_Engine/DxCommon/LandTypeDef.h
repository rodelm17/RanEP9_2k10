/*!
 * \file LandTypeDef.h
 *
 * \author Juver
 * \date March 2018
 *
 * 
 */
#pragma once

enum EM_LAND_TYPE
{
	EMLR_DAYNIGHT_ON = 0,	// ������ �ִ� ��Ʈ��
	EMLR_DAYNIGHT_OFF = 1,	// ������ ���� ��Ʈ��
	EMLR_PIECE = 2,			// Piece Object
};

enum EMOBJOCTREE_TYPE
{
	EMOBJOCTREE_TYPE_ORIG		= 0,
	EMOBJOCTREE_TYPE_LIGHTMAP	= 1,
	EMOBJOCTREE_TYPE_MATERIAL	= 2,
};

enum EMAABBCTREE_TYPE
{
	EMAABBCTREE_TYPE_ORIG		= 0,
	EMAABBCTREE_TYPE_LIGHTMAP	= 1,
};