#pragma once
#include "GameObject.h"
#include "Randomization.h"
#include "Delay.h"

namespace jm
{
	class Monster : public GameObject
	{
	protected:
		Delay calDirDelay;

		vec2 moveDir;
		float speed;
		float maxHp;
		float curHp;

		float originDelay; //�⺻ calDirDelay �ӽ����庯��
		float recogRad; //�÷��̾� �νİŸ�

		int dirFlag = 1;

	public:
		Monster(const vec2& position, const float& speed, const float& bodyRadius, const float& maxHp, const Delay& calDirDelay, const float& recogRad = 0.35f);

		//�̵�����
		void moveTo(const vec2& targetPos);
		void updateDir(const vec2& targetPos);
		void move();

		//��������
		void hit(const float& damage);
		//�׾����� Ȯ��
		bool checkDie();
		//render
		void render() const override;
		void drawHp() const;
		//pure virtual methods
		virtual void drawBody() const = 0;
		virtual RGB getColor() const = 0;
	};
}