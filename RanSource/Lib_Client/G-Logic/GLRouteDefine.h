/*!
 * \file GLRouteDefine.h
 *
 * \author Juver
 * \date 2020/10/24
 *
 * 
 */

#ifndef GLROUTEDEFINE_H_INCLUDED__
#define GLROUTEDEFINE_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	EMMONEY_LOG				= 10000,			// �α׸� ���游�� �ݾ׺�ȭ.
	EMCLUBINCOMEMONEY_LOG	= 100000000,	// Ŭ�� ���� �α�
};

// �������� ��ȯŸ��
enum EMITEM_ROUTE
{
	EMITEM_ROUTE_CHAR		= 0, // ĳ���Ͱ� �ŷ�
	EMITEM_ROUTE_GROUND		= 1, // �ٴڿ� ����
	EMITEM_ROUTE_SHOP		= 2, // ������ �Ǹ�,����
	EMITEM_ROUTE_USERINVEN	= 3, // ����� ��Ŀ�� �ֱ�, ����
	EMITEM_ROUTE_DELETE		= 4, // ������ ����
	EMITEM_ROUTE_CLUB		= 5, // Ŭ�� ��Ŀ�� �ֱ�, ����
	EMITEM_ROUTE_CLUBINCOME	= 6, // ����Ŭ�� ���� ����
	EMITEM_ROUTE_NPCREMAKE  = 7, // ���� �����ϰ� NPC ���Լ� ������ ������ġ ����
	EMITEM_ROUTE_PETCARD	= 8, // ��ī���� ��뿩��
	EMITEM_ROUTE_ODDEVEN	= 9, // Ȧ¦����
	EMITEM_ROUTE_VEHICLE	= 10, // ���� ���� �α�
	EMITEM_ROUTE_VNINVEN	= 11, // ��Ʈ�� Ž�� ���� �κ��丮���� ���� ������ ���
	EMITEM_ROUTE_GARBAGE	= 12, // ���������� ������ ������
	EMITEM_ROUTE_NPCCOME	= 13, // NPC ��ȯ���� ���� ������
	EMITEM_ROUTE_ITEMMIX	= 14, // ������ ����
	EMITEM_ROUTE_GATHERING	= 15, // ä��
	EMITEM_ROUTE_SYSTEM		= 16, // �ý������� �Ͼ �α�

	EMITEM_ROUTE_SIZE		= 17,
};

enum EMVEHICLE_ACTION
{
	EMVEHICLE_ACTION_BATTERY_BEFORE	= 0, // Ż�� ���͸� ��
	EMVEHICLE_ACTION_BATTERY_AFTER	= 1, // Ż�� ���͸� ��
	EMVEHICLE_ACTION_BOOSTER_ENABLE			= 2,	/*vehicle booster system, Juver, 2017/08/10 */
	EMVEHICLE_ACTION_BIKE_CHANGE_COLOR		= 3,	/*bike color , Juver, 2017/11/12 */
	EMVEHICLE_ACTION_CAR_CART_CHANGE_COLOR	= 4,	/* car, cart color, Juver, 2018/02/14 */

};

// �� �׼� Ÿ��
enum EMPET_ACTION
{
	EMPET_ACTION_FOOD_BEFORE	= 0, // �� ������
	EMPET_ACTION_FOOD_AFTER		= 1, // �� ������
	EMPET_ACTION_RENAME			= 2, // �� �̸�����
	EMPET_ACTION_COLOR			= 3, // �� �÷�����
	EMPET_ACTION_STYLE			= 4, // �� ��Ÿ�Ϻ���
	EMPET_ACTION_SKILL			= 5, // �� ��ų
	EMPET_ACTION_REVIVE			= 6, // �� ��Ȱī��
	EMPET_ACTION_PETSKINPACK	= 7,  // �� ��Ų ��

	EMPET_ACTION_PET_DUAL_SKILL	= 20, /*dual pet skill, Juver, 2017/12/29 */
};

#endif // GLROUTEDEFINE_H_INCLUDED__
