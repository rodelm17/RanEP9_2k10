#include "stdafx.h"

#include "DxSkinMeshContainer9.h"

#include "DxSkinMesh9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern DWORD SKINDRAWCOUNT;

//void DxSkinMesh9::DrawMeshCartoon( IDirect3DDevice9 *pd3dDevice, LPD3DXMESHCONTAINER pMeshContainerBase )
//{
//	HRESULT hr;
//    SMeshContainer *pMeshContainer = (SMeshContainer*)pMeshContainerBase;
//
//	DWORD dwNumInfl(0);
//	UINT NumAttributeGroups(0);
//	DWORD dwThisAttribId(0);
//	DXMATERIALEX* pMaterialEx(NULL);
//    UINT iMaterial;
//    UINT NumBlend;
//    UINT iAttrib;
//    DWORD AttribIdPrev;
//    LPD3DXBONECOMBINATION pBoneComb;
//	LPD3DXBONECOMBINATION pBoneCur;
//
//    UINT iMatrixIndex;
//    UINT iPaletteEntry;
//    D3DXMATRIXA16 matTemp, matBoneMatrix_UP;
//
//    // first check for skinning
//    if (pMeshContainer->pSkinInfo != NULL)
//    {
//        if( m_SkinningMethod == D3DNONINDEXED )
//        {
//            AttribIdPrev = UNUSED32; 
//            pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
//
//			// Draw using default vtx processing of the device (typically HW)
//			NumAttributeGroups = pMeshContainer->NumAttributeGroups;
//			for( iAttrib = 0; iAttrib < NumAttributeGroups; ++iAttrib )
//			{
//				pBoneCur = &pBoneComb[iAttrib];
//				dwThisAttribId = pBoneCur->AttribId;
//				pMaterialEx = &pMeshContainer->pMaterialEx[dwThisAttribId];
//				if( !pMaterialEx )	continue;
//
//				// Note : �ؽ��İ� ���� ���� ���� ���
//				if( !pMaterialEx->pTexture )
//				{
//					// Note : ���� �ε尡 �Ǿ����� ���캻��.
//					CheckLoadTexture( pd3dDevice, pMeshContainer, dwThisAttribId);
//				}
//
//				NumBlend = 0;
//				dwNumInfl = pMeshContainer->NumInfl;
//				for (DWORD i = 0; i < dwNumInfl; ++i)
//				{
//					if (pBoneCur->BoneId[i] != UINT_MAX)
//					{
//						NumBlend = i;
//					}
//				}
//
//				if( m_dwMaxVertexBlendMatrices >= NumBlend + 1 )
//				{
//					// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
//					for (DWORD i = 0; i < dwNumInfl; ++i)
//					{
//						iMatrixIndex = pBoneCur->BoneId[i];
//						if (iMatrixIndex != UINT_MAX)
//						{
//							D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
//							pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
//						}
//					}
//					
//
//					pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);
//
//					// lookup the material used for this subset of faces
//					if ((AttribIdPrev != dwThisAttribId) || (AttribIdPrev == UNUSED32))
//					{
//						pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[dwThisAttribId].MatD3D );
//						AttribIdPrev = dwThisAttribId;
//					}
//
//					++SKINDRAWCOUNT;
//					RenderDefault( pd3dDevice, pMeshContainer, iAttrib, dwThisAttribId, NULL, NULL );
//				}
//			}
//
//			// If necessary, draw parts that HW could not handle using SW
//			if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
//			{
//				AttribIdPrev = UNUSED32; 
//				V_PASS( pd3dDevice->SetSoftwareVertexProcessing(TRUE) );
//				for (iAttrib = pMeshContainer->iAttributeSW; iAttrib < pMeshContainer->NumAttributeGroups; ++iAttrib)
//				{
//					pBoneCur = &pBoneComb[iAttrib];
//					dwThisAttribId = pBoneCur->AttribId;
//					pMaterialEx = &pMeshContainer->pMaterialEx[dwThisAttribId];
//					if( !pMaterialEx )	continue;
//
//					// Note : �ؽ��İ� ���� ���� ���� ���
//					if( !pMaterialEx->pTexture )
//					{
//						// Note : ���� �ε尡 �Ǿ����� ���캻��.
//						CheckLoadTexture( pd3dDevice, pMeshContainer, dwThisAttribId);
//					}
//
//					NumBlend = 0;
//					dwNumInfl = pMeshContainer->NumInfl;
//					for (DWORD i = 0; i < dwNumInfl; ++i)
//					{
//						if (pBoneCur->BoneId[i] != UINT_MAX)
//						{
//							NumBlend = i;
//						}
//					}
//
//					if( m_dwMaxVertexBlendMatrices < NumBlend + 1)
//					{
//						// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
//						for (DWORD i = 0; i < dwNumInfl; ++i)
//						{
//							iMatrixIndex = pBoneCur->BoneId[i];
//							if (iMatrixIndex != UINT_MAX)
//							{
//								matBoneMatrix_UP = *pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex];
//								matBoneMatrix_UP._42 += m_fHeight;
//
//								D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], &matBoneMatrix_UP );
//								V_PASS( pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp ) );
//							}
//						}
//
//						V_PASS( pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend) );
//
//						// lookup the material used for this subset of faces
//						if ((AttribIdPrev != dwThisAttribId) || (AttribIdPrev == UNUSED32))
//						{
//							V_PASS( pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[dwThisAttribId].MatD3D ) );
//						//	V_PASS( pd3dDevice->SetTexture( 0, pMeshContainer->pMaterialEx[dwThisAttribId].pTexture ) );
//							AttribIdPrev = dwThisAttribId;
//						}
//
//						RenderDefault ( pd3dDevice, pMeshContainer, iAttrib, dwThisAttribId, NULL, NULL );
//					}
//				}
//				V_PASS( pd3dDevice->SetSoftwareVertexProcessing( FALSE ) );
//			}
//
//            V_PASS( pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, 0) );
//        }
//        else if (m_SkinningMethod == D3DINDEXEDHLSLVS) 
//        {
//			D3DXMATRIX matViewProj, matView, matProj;
//			pd3dDevice->GetTransform( D3DTS_VIEW, &matView );
//			pd3dDevice->GetTransform( D3DTS_PROJECTION, &matProj );
//			D3DXMatrixMultiply( &matViewProj, &matView, &matProj );
//			m_pEffect->SetMatrix( "mViewProj", &matViewProj );
//
//			// Set Light for vertex shader
//			D3DXVECTOR4 vLightDir( 0.0f, 1.0f, -1.0f, 0.0f );
//			D3DXVec4Normalize( &vLightDir, &vLightDir );
//			V_PASS( pd3dDevice->SetVertexShaderConstantF(1, (float*)&vLightDir, 1) );
//			V_PASS( m_pEffect->SetVector( "lhtDir", &vLightDir) );
//
//            if (pMeshContainer->UseSoftwareVP)
//            {
//                // If hw or pure hw vertex processing is forced, we can't render the
//                // mesh, so just exit out.  Typical applications should create
//                // a device with appropriate vertex processing capability for this
//                // skinning method.
//                if( m_dwBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING )
//                    return;
//
//                V_PASS( pd3dDevice->SetSoftwareVertexProcessing(TRUE) );
//            }
//
//            pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
//            for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; ++iAttrib)
//            { 
//				// first calculate all the world matrices
//				for (iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
//				{
//					iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
//					if (iMatrixIndex != UINT_MAX)
//					{
//						D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex] );
//					}
//				}
//
//                V_PASS( m_pEffect->SetMatrixArray( "mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries) );
//
//                // Sum of all ambient and emissive contribution
//                D3DXCOLOR color1(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Ambient);
//                D3DXCOLOR color2(.25, .25, .25, 1.0);
//                D3DXCOLOR ambEmm;
//                D3DXColorModulate(&ambEmm, &color1, &color2);
//                ambEmm += D3DXCOLOR(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Emissive);
//
//                // set material color properties 
//                V_PASS( m_pEffect->SetVector("MaterialDiffuse", (D3DXVECTOR4*)&(pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D.Diffuse)) );
//                V_PASS( m_pEffect->SetVector("MaterialAmbient", (D3DXVECTOR4*)&ambEmm) );
//
//                // setup the material of the mesh subset - REMEMBER to use the original pre-skinning attribute id to get the correct material id
//		//		V_PASS( pd3dDevice->SetTexture( 0, pMeshContainer->pMaterialEx[pBoneComb[iAttrib].AttribId].pTexture ) );
//
//                // Set CurNumBones to select the correct vertex shader for the number of bones
//                V_PASS( m_pEffect->SetInt( "CurNumBones", pMeshContainer->NumInfl -1) );
//
//                // Start the effect now all parameters have been updated
//                UINT numPasses;
//                V_PASS( m_pEffect->Begin( &numPasses, D3DXFX_DONOTSAVESTATE ) ); 
//                for( UINT iPass = 0; iPass < numPasses; iPass++ )
//                {
//                    V_PASS( m_pEffect->BeginPass( iPass ) );
//
//					 // draw the subset with the current world matrix palette and material state
//                 //   V_PASS( pMeshContainer->MeshData.pMesh->DrawSubset( iAttrib ) );
//
//					++SKINDRAWCOUNT;
//					RenderDefault ( pd3dDevice, pMeshContainer, iAttrib, dwThisAttribId, NULL, NULL );
//
//                    V_PASS( m_pEffect->EndPass() );
//                }
//
//                V_PASS( m_pEffect->End() );
//
//                V_PASS( pd3dDevice->SetVertexShader(NULL) );
//            }
//
//            // remember to reset back to hw vertex processing if software was required
//            if (pMeshContainer->UseSoftwareVP)
//            {
//                V_PASS( pd3dDevice->SetSoftwareVertexProcessing(FALSE) );
//            }
//        }
//        else // bug out as unsupported mode
//        {
//            return;
//        }
//    }
//    else  // standard mesh, just draw it after setting material properties
//    {
//		D3DXMATRIX matCombined;
//		D3DXMatrixMultiply ( &matCombined, pMeshContainer->ppBoneMatrixPtrs[1], pMeshContainer->ppBoneMatrixPtrs[2] );
//		D3DXMatrixMultiply ( &matCombined, pMeshContainer->ppBoneMatrixPtrs[0], &matCombined );
//
//		matCombined._42 += m_fHeight;
//		m_matWorld = matCombined;		// �ܵ� Eff ���� ���� ���̴�.
//
//		V_PASS( pd3dDevice->SetTransform(D3DTS_WORLD, &matCombined) );
//
//		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
//		{
//			DXMATERIALEX* pMaterialEx = &pMeshContainer->pMaterialEx[iMaterial];
//			if( !pMaterialEx )	continue;
//
//			// Note : �ؽ��İ� ���� ���� ���� ���
//			if( !pMaterialEx->pTexture )
//			{
//				// Note : ���� �ε尡 �Ǿ����� ���캻��.
//				CheckLoadTexture( pd3dDevice, pMeshContainer, iMaterial );
//			}
//
//			V_PASS( pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D ) );
//		//	V_PASS( pd3dDevice->SetTexture( 0, pMeshContainer->pMaterialEx[iMaterial].pTexture ) );
//
//			RenderDefault ( pd3dDevice, pMeshContainer, iMaterial, iMaterial, NULL, NULL );
//		}
//    }
//}










