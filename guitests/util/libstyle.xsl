<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:mlib="http://dvnci/mlib"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
extension-element-prefixes="mlib">
    
    
    <xsl:template name="lib_svgstyle"> 
        <defs>
            <xsl:call-template name="apply_lib_filterstyle"/>
            <xsl:call-template name="apply_lib_gradients"/> 
        </defs>  
    </xsl:template>

 
   <xsl:template name="apply_lib_filterstyle"> 

 
       <filter id="filter_lib_armat1000"  x="-20%" y="-20%" width="140%" height="140%">
            <feGaussianBlur in="SourceAlpha" stdDeviation="40" result="blur"/>
            <feSpecularLighting in="blur" surfaceScale="5" specularConstant=".75" specularExponent="20" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="50000" y="50000" z="200000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint"/>
            <feMerge>
                <!--feMergeNode in="offsetBlur"/-->
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>
        
        <filter id="filter_lib1" x="0%" y="0%" width="100%" height="100%">
            <feGaussianBlur in="SourceAlpha" stdDeviation="40" result="blur"/>
            <feSpecularLighting in="blur" surfaceScale="5" specularConstant=".75" specularExponent="20" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="50000" y="100000" z="200000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint"/>
            <feMerge>
                <!--feMergeNode in="offsetBlur"/-->
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>

        <filter id="filter_lib2"  x="-10%" y="-10%" width="120%" height="120%" >
            <feGaussianBlur in="SourceAlpha" stdDeviation="4" result="blur"/>
            <feSpecularLighting in="blur" surfaceScale="6" specularConstant=".6" specularExponent="5" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="0" y="0" z="20000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint">
            </feComposite>    
            <feMerge>
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>
        

        <filter id="filter_lib3" filterUnits="userSpaceOnUse" x="0%" y="0%" width="100%" height="100%" >
            <feGaussianBlur in="SourceAlpha" stdDeviation="4" result="blur"/>
            <feSpecularLighting in="blur" surfaceScale="10" specularConstant=".75" specularExponent="20" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="0" y="0" z="20000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint">
            </feComposite>    
            <feMerge>
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>
        
        <filter id="filter_lib4" filterUnits="userSpaceOnUse">
            <feGaussianBlur in="SourceAlpha" stdDeviation="4" result="blur"/>
            <feSpecularLighting in="blur" surfaceScale="10" specularConstant=".75" specularExponent="20" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="0" y="0" z="20000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint">
            </feComposite>    
            <feMerge>
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>
        
        <filter id="filter_null">
        </filter>

     </xsl:template>   
     
     
     
     
     <xsl:template name="apply_lib_gradients"> 
    
          <!--linearGradient id="gradientnone_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#F7F7F7"/>
		<stop  offset="0.5" style="stop-color:#D1D1D1"/>
		<stop  offset="1" style="stop-color:#ECECEC"/>
	</linearGradient>
        
        <linearGradient id="gradientnone_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#F7F7F7"/>
		<stop  offset="0.5" style="stop-color:#D1D1D1"/>
		<stop  offset="1" style="stop-color:#ECECEC"/>
	</linearGradient>
        
        <radialGradient id="gradientnone_c">
		<stop  offset="0" style="stop-color:#F7F7F7"/>
		<stop  offset="1" style="stop-color:#D1D1D1"/>
	</radialGradient>
        
        
        
          <linearGradient id="gradientblack_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#333"/>
		<stop  offset="0.5" style="stop-color:#000"/>
		<stop  offset="1" style="stop-color:#333"/>
	</linearGradient>
        
        <linearGradient id="gradienblack_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#000"/>
		<stop  offset="0.5" style="stop-color:#333"/>
		<stop  offset="1" style="stop-color:#000"/>
	</linearGradient>
        
        <radialGradient id="gradientblack_c">
		<stop  offset="0" style="stop-color:#333"/>
		<stop  offset="1" style="stop-color:#000"/>
	</radialGradient>        
                


	<linearGradient id="gradientalarm_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#a92"/>
		<stop  offset="0.5" style="stop-color:#f92"/>
		<stop  offset="1" style="stop-color:#f92"/>
	</linearGradient>
        
        <linearGradient id="gradientalarm_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#a92"/>
		<stop  offset="0.5" style="stop-color:#f92"/>
		<stop  offset="1" style="stop-color:#f92"/>
	</linearGradient>
        
        <radialGradient id="gradientalarm_c">
		<stop  offset="0" style="stop-color:#a92"/>
		<stop  offset="0.5" style="stop-color:#f92"/>
	</radialGradient>   
        
        
        
        <linearGradient id="gradientaccident_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AA0000"/>
		<stop  offset="0.5" style="stop-color:#FF0000"/>
		<stop  offset="1" style="stop-color:#AA0000"/>
	</linearGradient>
        
        <linearGradient id="gradientaccident_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AA0000"/>
		<stop  offset="0.5" style="stop-color:#FF0000"/>
		<stop  offset="1" style="stop-color:#AA0000"/>
	</linearGradient>
        
        <radialGradient id="gradientaccident_c">
		<stop  offset="0" style="stop-color:#AA0000"/>
		<stop  offset="1" style="stop-color:#FF0000"/>
	</radialGradient>
        
        
        <linearGradient id="gradientnotice_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AAAA00"/>
		<stop  offset="0.5" style="stop-color:#FFFF00"/>
		<stop  offset="1" style="stop-color:#AAAA00"/>
	</linearGradient>
        
        <linearGradient id="gradientnotice_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AAAA00"/>
		<stop  offset="0.5" style="stop-color:#FFFF00"/>
		<stop  offset="1" style="stop-color:#AAAA00"/>
	</linearGradient>
        
        <radialGradient id="gradientnotice_c">
		<stop  offset="0" style="stop-color:#AAAA00"/>
		<stop  offset="1" style="stop-color:#FFFF00"/>
	</radialGradient>        
        

        
        <linearGradient id="gradientgaz_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FFFF44"/>
		<stop  offset="0.5" style="stop-color:#DDDD22"/>
		<stop  offset="1" style="stop-color:#FFFF44"/>
	</linearGradient>
        
        <linearGradient id="gradientgaz_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FFFF44"/>
		<stop  offset="0.5" style="stop-color:#DDDD22"/>
		<stop  offset="1" style="stop-color:#FFFF44"/>
	</linearGradient> 
        
        <radialGradient id="gradientgaz_c">
		<stop  offset="0" style="stop-color:#FFFF44"/>
		<stop  offset="1" style="stop-color:#DDDD22"/>
	</radialGradient>         
        
        
        
        <linearGradient id="gradientwater_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55FFAA"/>
		<stop  offset="0.5" style="stop-color:#33CC99"/>
		<stop  offset="1" style="stop-color:#55FFAA"/>
	</linearGradient>
        
        <linearGradient id="gradientwater_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55FFAA"/>
		<stop  offset="0.5" style="stop-color:#33CC99"/>
		<stop  offset="1" style="stop-color:#55FFAA"/>
	</linearGradient>
        
        <radialGradient id="gradientwater_c">
		<stop  offset="0" style="stop-color:#55FFAA"/>
		<stop  offset="1" style="stop-color:#33CC99"/>
	</radialGradient> 
        
        
        
        <linearGradient id="gradientair_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55BBFF"/>
		<stop  offset="0.5" style="stop-color:#3399FF"/>
		<stop  offset="1" style="stop-color:#55BBFF"/>
	</linearGradient>
        
        <linearGradient id="gradientair_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55BBFF"/>
		<stop  offset="0.5" style="stop-color:#3399FF"/>
		<stop  offset="1" style="stop-color:#55BBFF"/>
	</linearGradient> 
        
        <radialGradient id="gradientair_c">
		<stop  offset="0" style="stop-color:#55BBFF"/>
		<stop  offset="1" style="stop-color:#3399FF"/>
	</radialGradient>         
        
        
        
        <linearGradient id="gradientoil_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FF8855"/>
		<stop  offset="0.5" style="stop-color:#CC6633"/>
		<stop  offset="1" style="stop-color:#FF8855"/>
	</linearGradient>
        
        <linearGradient id="gradientoil_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FF8855"/>
		<stop  offset="0.5" style="stop-color:#CC6633"/>
		<stop  offset="1" style="stop-color:#FF8855"/>
	</linearGradient> 
        
        <radialGradient id="gradientoil_c">
		<stop  offset="0" style="stop-color:#FF8855"/>
		<stop  offset="1" style="stop-color:#CC6633"/>
	</radialGradient>         
        
        
        
        <linearGradient id="gradientstream_h"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#CC33CC"/>
		<stop  offset="0.5" style="stop-color:#FF00FF"/>
		<stop  offset="1" style="stop-color:#CC33CC"/>
	</linearGradient>
        
        <linearGradient id="gradientstrem_v"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#CC33CC"/>
		<stop  offset="0.5" style="stop-color:#FF00FF"/>
		<stop  offset="1" style="stop-color:#CC33CC"/>
	</linearGradient> 
 
        <radialGradient id="gradientstrem_c">
		<stop  offset="0" style="stop-color:#CC33CC"/>
		<stop  offset="1" style="stop-color:#FF00FF"/>
	</radialGradient-->       
        
    
     </xsl:template>     
    
    



</xsl:stylesheet>
