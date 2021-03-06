// Caption: Color solid pigment include v1.3.1
// Authors: Michael Horvath, http://isometricland.net
// Created: 2008-06-22
// Updated: 2020-01-19
// This file is licensed under the terms of the CC-LGPL.

#version 3.7

//------------------------------
// Functions & variables

#declare CSolid_Offset = 0.000001;
#declare CSolid_EllSphere_Function = function(x,y,z) {sqrt(pow(x,2) + pow(z,2)) / cos(asin(abs(y)))}
#declare CSolid_DblCone_Function = function {sqrt(pow(x,2) + pow(z,2)) / (1-abs(y))}
#declare CSolid_Cone_Function = function {sqrt(pow(x,2) + pow(z,2))/y}


//------------------------------
// HSL Cube

#declare CSolid_HSLCube_Hue = pigment
{
	gradient x
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSLCube_Saturation = pigment
{
	gradient z
	pigment_map
	{
		[0 color srgb 1/2]
		[1 CSolid_HSLCube_Hue]
	}
}
#declare CSolid_HSLCube_Lightness = pigment
{
	gradient y
	pigment_map
	{
		[0/2 color srgb 0]
		[1/2 CSolid_HSLCube_Saturation]
		[2/2 color srgb 1]
	}
}
#declare CSolid_HSLCube_Pigment = pigment
{
	CSolid_HSLCube_Lightness
	scale		(1 + CSolid_Offset)
	translate	-CSolid_Offset/2
}


//------------------------------
// HSL Cylinder

#declare CSolid_HSLCylinder_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSLCylinder_Saturation = pigment
{
	cylindrical
	pigment_map
	{
		[0 CSolid_HSLCylinder_Hue]
		[1 color srgb 1/2]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_HSLCylinder_Lightness = pigment
{
	gradient y
	pigment_map
	{
		[0/2 color srgb 0]
		[1/2 CSolid_HSLCylinder_Saturation]
		[2/2 color srgb 1]
	}
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_HSLCylinder_Pigment = pigment {CSolid_HSLCylinder_Lightness}


//------------------------------
// HSL Double-cone


#declare CSolid_HSLDblCone_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSLDblCone_Saturation = pigment
{
	function {CSolid_DblCone_Function(x,y,z)}
	pigment_map
	{
		[0 color srgb 1/2]
		[1 CSolid_HSLDblCone_Hue]
	}
	translate	+y
	scale		y/2
	scale		(1 + CSolid_Offset)
}
#declare CSolid_HSLDblCone_Lightness = pigment
{
	gradient y
	pigment_map
	{
		[0/2 color srgb 0]
		[1/2 CSolid_HSLDblCone_Saturation]
		[2/2 color srgb 1]
	}
	scale		y * 2
	translate	-y
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_HSLDblCone_Pigment = pigment {CSolid_HSLDblCone_Lightness}


//------------------------------
// HSL Parametric Sphere

#declare CSolid_HSLSphere_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSLSphere_Saturation = pigment
{
	function {f_r(x,y,z)}
	pigment_map
	{
		[0 color srgb 1/2]
		[1 CSolid_HSLSphere_Hue]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_HSLSphere_Lightness = pigment
{
	function {f_ph(x,y,z)/pi}
	pigment_map
	{
		[0/2 color srgb 1]
		[1/2 CSolid_HSLSphere_Saturation]
		[2/2 color srgb 0]
	}
}
#declare CSolid_HSLSphere_Pigment = pigment {CSolid_HSLSphere_Lightness}


//------------------------------
// HSL Parametric Sphere with hole

#declare CSolid_HSLSphereHole_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSLSphereHole_Saturation = pigment
{
	function {f_r(x,y,z)}
	pigment_map
	{
		[0/7 color srgb 1/2]
		[1/7 color srgb 1/2]
		[7/7 CSolid_HSLSphereHole_Hue]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_HSLSphereHole_Lightness = pigment
{
	function {f_ph(x,y,z)/pi}
	pigment_map
	{
		[0/2 color srgb 1]
		[1/2 CSolid_HSLSphereHole_Saturation]
		[2/2 color srgb 0]
	}
}
#declare CSolid_HSLSphereHole_Pigment = pigment {CSolid_HSLSphereHole_Lightness}

// hole only
#declare CSolid_HSLHole_Saturation = pigment
{
	color srgb 1/2
}
#declare CSolid_HSLHole_Lightness = pigment
{
	function {f_ph(x,y,z)/pi}
	pigment_map
	{
		[0/2 color srgb 1]
		[1/2 CSolid_HSLHole_Saturation]
		[2/2 color srgb 0]
	}
}
#declare CSolid_HSLHole_Pigment = pigment {CSolid_HSLHole_Lightness}


//------------------------------
// HSL Ellipsoidal Sphere

#declare CSolid_HSLEllSphere_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSLEllSphere_Saturation = pigment
{
	function {CSolid_EllSphere_Function(x,y,z)}
	pigment_map
	{
		[0 color srgb 1/2]
		[1 CSolid_HSLEllSphere_Hue]
	}
	translate	+y
	scale		y/2
	scale		(1 + CSolid_Offset)
}
#declare CSolid_HSLEllSphere_Lightness = pigment
{
	gradient y
	pigment_map
	{
		[0/2 color srgb 0]
		[1/2 CSolid_HSLEllSphere_Saturation]
		[2/2 color srgb 1]
	}
	scale		y * 2
	translate	-y
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_HSLEllSphere_Pigment = pigment {CSolid_HSLEllSphere_Lightness}


//------------------------------
// HSV Cube

#declare CSolid_HSVCube_Hue = pigment
{
	gradient x
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSVCube_WhiteToHue = pigment
{
	gradient z
	pigment_map
	{
		[0 color srgb 1]
		[1 CSolid_HSVCube_Hue]
	}
}
#declare CSolid_HSVCube_Value = pigment
{
	gradient y
	pigment_map
	{
		[0 color srgb 0]
		[1 CSolid_HSVCube_WhiteToHue]
	}
}
#declare CSolid_HSVCube_Pigment = pigment
{
	CSolid_HSVCube_Value
	scale		(1 + CSolid_Offset)
	translate	-CSolid_Offset/2
}


//------------------------------
// HSV Cone

#declare CSolid_HSVCone_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSVCone_WhiteToHue = pigment
{
	function {CSolid_Cone_Function(x,y,z)}
	pigment_map
	{
		[0 color srgb 1]
		[1 CSolid_HSVCone_Hue]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_HSVCone_Value = pigment
{
	gradient y
	pigment_map
	{
		[0 color srgb 0]
		[1 CSolid_HSVCone_WhiteToHue]
		
	}
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_HSVCone_Pigment = pigment {CSolid_HSVCone_Value}


//------------------------------
// HSV Cylinder

#declare CSolid_HSVCylinder_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSVCylinder_WhiteToHue = pigment
{
	cylindrical
	pigment_map
	{
		[0 CSolid_HSVCylinder_Hue]
		[1 color srgb 1]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_HSVCylinder_Value = pigment
{
	gradient y
	pigment_map
	{
		[0 color srgb 0]
		[1 CSolid_HSVCylinder_WhiteToHue]
	}
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_HSVCylinder_Pigment = pigment {CSolid_HSVCylinder_Value}


//------------------------------
// HSV Parametric sphere

#declare CSolid_HSVSphere_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1,0,0,>]
		[1/6 srgb <1,1,0,>]
		[2/6 srgb <0,1,0,>]
		[3/6 srgb <0,1,1,>]
		[4/6 srgb <0,0,1,>]
		[5/6 srgb <1,0,1,>]
		[6/6 srgb <1,0,0,>]
	}
}
#declare CSolid_HSVSphere_WhiteToHue = pigment
{
	function {f_r(x,y,z)}
	pigment_map
	{
		[0 color srgb 1]
		[1 CSolid_HSVSphere_Hue]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_HSVSphere_Value = pigment
{
	function {f_ph(x,y,z)/pi}
	pigment_map
	{
		[0 CSolid_HSVSphere_WhiteToHue]
		[1 color srgb 0]
	}
}
#declare CSolid_HSVSphere_Pigment = pigment {CSolid_HSVSphere_Value}


//------------------------------
// HSV Ellipsoidal Sphere

#declare CSolid_HSVEllSphere_Hue = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0/6 srgb <1, 0, 0,>]
		[1/6 srgb <1, 1, 0,>]
		[2/6 srgb <0, 1, 0,>]
		[3/6 srgb <0, 1, 1,>]
		[4/6 srgb <0, 0, 1,>]
		[5/6 srgb <1, 0, 1,>]
		[6/6 srgb <1, 0, 0,>]
	}
}
#declare CSolid_HSVEllSphere_WhiteToHue = pigment
{
	function {CSolid_EllSphere_Function(x,y,z)}
	pigment_map
	{
		[0 color srgb 1]
		[1 CSolid_HSVEllSphere_Hue]
	}
	translate	+y
	scale		y/2
	scale		(1 + CSolid_Offset)
}
#declare CSolid_HSVEllSphere_Value = pigment
{
	gradient y
	pigment_map
	{
		[0 color srgb 0]
		[1 CSolid_HSVEllSphere_WhiteToHue]
	}
	scale		y * 2
	translate	-y
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_HSVEllSphere_Pigment = pigment {CSolid_HSVEllSphere_Value}


//------------------------------
// RGB Cube

#declare CSolid_RGBCube_Red = pigment
{
	gradient x
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <3, 0, 0,>]
	}
}
#declare CSolid_RGBCube_Green = pigment
{
	gradient y
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <0, 3, 0,>]
	}
}
#declare CSolid_RGBCube_Blue = pigment
{
	gradient z
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <0, 0, 3,>]
	}
}
#declare CSolid_RGBCube_Pigment = pigment
{
	average
	pigment_map
	{
		[CSolid_RGBCube_Red]
		[CSolid_RGBCube_Green]
		[CSolid_RGBCube_Blue]
	}
	scale		(1 + CSolid_Offset)
	translate	-CSolid_Offset/2
}


//------------------------------
// RGB Cylinder

#declare CSolid_RGBCylinder_Red = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <3, 0, 0,>]
	}
}
#declare CSolid_RGBCylinder_Green = pigment
{
	cylindrical
	color_map
	{
		[0 srgb <0, 3, 0,>]
		[1 srgb <0, 0, 0,>]
	}
}
#declare CSolid_RGBCylinder_Blue = pigment
{
	gradient y
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <0, 0, 3,>]
	}
	scale		(1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_RGBCylinder_Pigment = pigment
{
	average
	pigment_map
	{
		[CSolid_RGBCylinder_Red]
		[CSolid_RGBCylinder_Green]
		[CSolid_RGBCylinder_Blue]
	}
}


//------------------------------
// RGB Parametric sphere

#declare CSolid_RGBSphere_Red = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <3, 0, 0,>]
	}
}
#declare CSolid_RGBSphere_Green = pigment
{
	function {f_r(x,y,z)}
	color_map
	{
		[0 srgb <0, 0, 0,>]
		[1 srgb <0, 3, 0,>]
	}
	scale	(1 + CSolid_Offset)
}
#declare CSolid_RGBSphere_Blue = pigment
{
	function {f_ph(x,y,z)/pi}
	color_map
	{
		[0 srgb <0, 0, 3,>]
		[1 srgb <0, 0, 0,>]
	}
}
#declare CSolid_RGBSphere_Pigment = pigment
{
	average
	pigment_map
	{
		[CSolid_RGBSphere_Red]
		[CSolid_RGBSphere_Green]
		[CSolid_RGBSphere_Blue]
	}
	scale		(1 + CSolid_Offset)
	translate	-CSolid_Offset/2
}


//------------------------------
// RGB Ellipsoidal Sphere
// This one doesn't work for some reason.

#declare CSolid_RGBEllSphere_Red = pigment
{
	function {-f_th(x,y,z)/pi/2}
	color_map
	{
		[0 color srgb 0]
		[1 color srgb x]
	}
}
#declare CSolid_RGBEllSphere_Green = pigment
{
	function {CSolid_EllSphere_Function(x,y,z)}
	pigment_map
	{
		[0 color srgb 0]
		[1 color srgb y]
	}
	translate	+y
	scale		y/2
	scale		(1 + CSolid_Offset)
}
#declare CSolid_RGBEllSphere_Blue = pigment
{
	gradient y
	color_map
	{
		[1 srgb 0]
		[0 srgb z]
	}
	scale		y * 2
	translate	-y
	scale		y * (1 + CSolid_Offset)
	translate	-y * CSolid_Offset/2
}
#declare CSolid_RGBEllSphere_Pigment = pigment
{
	average
	pigment_map
	{
		[CSolid_RGBEllSphere_Red]
		[CSolid_RGBEllSphere_Green]
		[CSolid_RGBEllSphere_Blue]
	}
}
