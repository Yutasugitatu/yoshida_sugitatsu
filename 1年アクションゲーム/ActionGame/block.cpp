#include "main.h"
#include "block.h"
#include "Player.h"
#include "goal.h"
#include "game.h"
#include "sound.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_apTextureBlock[MAX_TYPE_BLOCK] = { 0 }; //�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL; //���_�o�b�t�@�̃|�C���g
BLOCK g_aBlock[MAX_BLOCK];
BLOCKTYPE Blocktype = BLOCKTYPE_NONE;
#define BLOCK_MOVE (2.0f)
int nCnt = 10;
int findex;
float g_fScrollGoal;
//float g_fScrollBlock;
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;
	int nCntBlock;
	g_fScrollGoal = 0.0f;
	//g_fScrollBlock = 0.0f;
	//�G�̏��̏�����
	for (nCntBlock = 0; nCntBlock <MAX_BLOCK; nCntBlock++)
	{
		/*g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/
		g_aBlock[nCntBlock].bUse = false;
	}
	//�e�N�X�`���̂�݂���
	D3DXCreateTextureFromFile(pDevice, "block.png", &g_apTextureBlock[BLOCKTYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "Blockda.png", &g_apTextureBlock[BLOCKTYPE_DAMAGE]);
	D3DXCreateTextureFromFile(pDevice, "JUMP.png", &g_apTextureBlock[BLOCKTYPE_JUMP]);
	D3DXCreateTextureFromFile(pDevice, "Goalblock.png", &g_apTextureBlock[BLOCKTYPE_GOAL]);
	/*D3DXCreateTextureFromFile(pDevice, "enemy002.png", &g_apTextureEnemy[2]);*/
	//�I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL);
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2), 0.0f);
		//�������̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//�A�����b�N
	g_pVtxBuffBlock->Unlock();
}
//�I������
void UninitBlock(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_BLOCK; nCntTex++)
	{
		if (g_apTextureBlock[nCntTex] != NULL)
		{
			g_apTextureBlock[nCntTex]->Release();
			g_apTextureBlock[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//�X�V����
void UpdateBlock(void)
{
	VERTEX_2D*pVtx;
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	int nCntBlock;
	float g_fScrollBlock = 10.0f;
	float g_fScrollBlockAIR = 23.0f;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)//block���g�p����Ă�
		{
			if (pPlayer->bLife == true)
			{
				if (pPlayer->scrollR == true)
				{
					pPlayer->scrollL = false;
					g_aBlock[nCntBlock].pos.x += -g_fScrollBlock/**BLOCK_MOVE*/;
					if (GetKeyBoardPress(DIK_LSHIFT))//dash
					{
						g_aBlock[nCntBlock].pos.x += -5.0;
					}
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				if (pPlayer->scrollL == true)
				{
					pPlayer->scrollR = false;
					g_aBlock[nCntBlock].pos.x += g_fScrollBlock/**BLOCK_MOVE*/;
					if (GetKeyBoardPress(DIK_LSHIFT))//dash
					{
						g_aBlock[nCntBlock].pos.x += 5.0;
					}
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				if (pPlayer->scrollUP == true)
				{
					g_aBlock[nCntBlock].pos.y += g_fScrollBlockAIR/**BLOCK_MOVE*/;

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				if (pPlayer->scrollDOWN == true)
				{
					g_aBlock[nCntBlock].pos.y += -g_fScrollBlockAIR/**BLOCK_MOVE*/;

					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
				}
				
			}
		}
		pVtx += 4;
	}
	
	//�A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//�`�揈��
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntBlock;
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�|���S���̕`��
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)//�G���g�p���Ȃ�`��
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, NUM_POLYGON);
		}
	}
}
//�G�̐ݒ菈��
void SetBlock(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D*pVtx;
	int nCntBlock;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)//�G���g�p����Ă��Ȃ�
		{
			g_aBlock[nCntBlock].pos = pos;
			//[nCntBlock].pos =g_aBlock[nCntBlock].move;
			g_aBlock[nCntBlock].nType = nType;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (-BLOCK_SIZE_Y / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (-BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + (+BLOCK_SIZE_X / 2), g_aBlock[nCntBlock].pos.y + (+BLOCK_SIZE_Y / 2), 0.0f);
			g_aBlock[nCntBlock].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffBlock->Unlock();
}
//�G�̉
BLOCK*GetBlock(void)
{
	return &g_aBlock[0];
}
bool CollisionBlock(D3DXVECTOR3*pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3*pMove, D3DXVECTOR3 Size)
{
	bool bLnad = false;
	PLAYER*pPlayer;
	pPlayer = GetPlayer();
	int nCntBlock;
	//************************************************************************************
	//Block�Ƃ̓����蔻��
	//************************************************************************************
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCKTYPE_NORMAL:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 1)
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 1)
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1))
				{
					if (pPlayer->pos.y - (PLAYER_SIZE_Y / 2) < g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1
						&& pPlayer->posOld.y - (PLAYER_SIZE_Y / 2) >= g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)//��
					{
						if (pPlayer->move.y < 0)
						{
							pPlayer->move.y = 0.0f;
						}
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) + (PLAYER_SIZE_Y / 2);
					}
					if (pPlayer->pos.y + (PLAYER_SIZE_Y / 2) > g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1
						&& pPlayer->posOld.y + (PLAYER_SIZE_Y / 2) <= g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1)//��
					{
						pPlayer->bJump = false;
						pPlayer->nJump = false;
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) - (PLAYER_SIZE_Y / 2);
						if (pPlayer->move.y > 0)
						{
							pPlayer->move.y = 0.0f;
						}
					}
					else if (pPlayer->pos.x - (PLAYER_SIZE_X / 3) < g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 2
						&& pPlayer->posOld.x - (PLAYER_SIZE_X / 3) >= g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 2)//�E
					{
						pPlayer->scrollR = false;
						pPlayer->scrollL = false;
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + (PLAYER_SIZE_X / 3);

					}
					else if (pPlayer->pos.x + (PLAYER_SIZE_X / 3) > g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 2
						&& pPlayer->posOld.x + (PLAYER_SIZE_X / 3) <= g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 2)//��
					{
						pPlayer->scrollL = false;
						pPlayer->scrollR = false;
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) - (PLAYER_SIZE_X / 3);
					}

				}
				break;
			case BLOCKTYPE_DAMAGE:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2))
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2))
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3))
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4)))
				{
					if (pPlayer->pos.y - (PLAYER_SIZE_Y / 2) < g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3)
						&& pPlayer->posOld.y - (PLAYER_SIZE_Y / 2) >= g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3))//��
					{
						if (pPlayer->move.y < 0)
						{
							pPlayer->move.y = 0.0f;
						}
						HitPlayer(10);
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 3) + (PLAYER_SIZE_Y / 2);
						
					}
					if (pPlayer->pos.y + (PLAYER_SIZE_Y / 2) > g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4)
						&& pPlayer->posOld.y + (PLAYER_SIZE_Y / 2) <= g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4) )//��
					{
						pPlayer->bJump = false;
						pPlayer->nJump = false;
						HitPlayer(10);
						pPlayer->pos.y = g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 4) - (PLAYER_SIZE_Y / 2);
						if (pPlayer->move.y > 0)
						{
							pPlayer->move.y = 0.0f;
						}
						
					}
					else if (pPlayer->pos.x - (PLAYER_SIZE_X / 3) < g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) 
						&& pPlayer->posOld.x - (PLAYER_SIZE_X / 3) >= g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2))//�E
					{
						pPlayer->scrollR = false;	
						pPlayer->scrollL = false;
						HitPlayer(10);
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) + (PLAYER_SIZE_X / 3);

					}
					else if (pPlayer->pos.x + (PLAYER_SIZE_X / 3) > g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2)
						&& pPlayer->posOld.x + (PLAYER_SIZE_X / 3) <= g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2))//��
					{
						pPlayer->scrollL = false;
						pPlayer->scrollR = false;
						HitPlayer(10);
						pPlayer->pos.x = g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) - (PLAYER_SIZE_X / 3);
					}
				}
				break;
			case BLOCKTYPE_JUMP:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 1)
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 1)
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1))
				{
					if (GetKeyBoardTrigger(DIK_SPACE))//�W�����v
						{
						//PlaySound(SOUND_LABEL_JUMP);
						pPlayer->move.y = -40.0f;
						}
				}
				break;
			case BLOCKTYPE_GOAL:
				if ((pPlayer->pos.x - (PLAYER_SIZE_X / 3)) <= (g_aBlock[nCntBlock].pos.x + (BLOCK_SIZE_X / 2) - 1)
					&& (pPlayer->pos.x + (PLAYER_SIZE_X / 3)) >= (g_aBlock[nCntBlock].pos.x - (BLOCK_SIZE_X / 2) + 1)
					&& (pPlayer->pos.y - (PLAYER_SIZE_Y / 2)) <= (g_aBlock[nCntBlock].pos.y + (BLOCK_SIZE_Y / 2) - 1)
					&& (pPlayer->pos.y + (PLAYER_SIZE_Y / 2)) >= (g_aBlock[nCntBlock].pos.y - (BLOCK_SIZE_Y / 2) + 1))
				{
					SetGameState(GAMESTATE_CLEAR);
				}
				break;
			}
		}
	}
	if (g_aBlock[MAX_BLOCK].pos.y > SCREEN_HEIGHT)
	{
		pPos->y = SCREEN_HEIGHT;
		pMove->y = 0.0f;
		bLnad = true;
	}
	return bLnad;
}
