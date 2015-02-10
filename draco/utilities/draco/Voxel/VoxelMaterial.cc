using UnityEngine;
using System.Collections;

namespace Vox {

	[System.Serializable]
	public class VoxelMaterial {

		public string name;
		public Material renderMaterial;
		//public Texture2D topTexture, sideTexture, bottomTexture;
		//public Color color = Color.white;
		//public Color specularColor = Color.black;
		//public float roughness = 20;
		//public float blendTightness = 4;

		// physics
		public float strength = 10;
		public float pliability = 10;
		public float conductivity = 1;

		public VoxelMaterial() {
			//this.color = Color.white;
			//this.specularColor = Color.black;
			//this.roughness = 20;
			//this.blendTightness = 4;
			this.strength = 10;
			this.pliability = 10;
			this.conductivity = 1;
		}

		public VoxelMaterial(
			string name,
			Material renderMaterial,
			//Texture2D topTex, Texture2D sideTex, Texture2D bottomTex,
			//Color color, Color specularColor,
			//float roughness, float blendTightness,
			float strength, float pliability, float conductivity
			) {
			this.name = name;
			this.renderMaterial = renderMaterial;
			//this.topTexture = topTex;
			//this.sideTexture = sideTex;
			//this.bottomTexture = bottomTex;
			//this.color = color;
			//this.specularColor = specularColor;
			//this.roughness = roughness;
			//this.blendTightness = blendTightness;
			this.strength = strength;
			this.pliability = pliability;
			this.conductivity = conductivity;
		}
	}
}