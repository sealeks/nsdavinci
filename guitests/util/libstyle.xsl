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

        <!-- light gray -->
        <linearGradient id="__gradient_mlib_light_gray_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#aaa"/>
            <stop offset="0.5" stop-color="#fff"/>
            <stop offset="1" stop-color="#aaa"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_light_gray_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#aaa"/>
            <stop offset="0.5" stop-color="#fff"/>
            <stop offset="1" stop-color="#aaa"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_light_gray_c">
		<stop  offset="0" style="stop-color:#aaa"/>
		<stop  offset="1" style="stop-color:#fff"/>
	</radialGradient>
       
        <!-- midle gray -->
        <linearGradient id="__gradient_mlib_midle_gray_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#666"/>
            <stop offset="0.5" stop-color="#999"/>
            <stop offset="1" stop-color="#666"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_gray_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#999"/>
            <stop offset="0.5" stop-color="#666"/>
            <stop offset="1" stop-color="#999"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_gray_ho" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#666"/>
            <stop offset="0.5" stop-color="#999"/>
            <stop offset="1" stop-color="#666"/>
        </linearGradient>        
        <radialGradient id="__gradient_mlib_midle_gray_c">
		<stop  offset="0" style="stop-color:#666"/>
		<stop  offset="1" style="stop-color:#999"/>
	</radialGradient>
        
        <!-- dark gray -->
        <linearGradient id="__gradient_mlib_dark_gray_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#111"/>
            <stop offset="0.5" stop-color="#333"/>
            <stop offset="1" stop-color="#111"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_dark_fill" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#111"/>
            <stop offset="0.5" stop-color="#333"/>
            <stop offset="1" stop-color="#111"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_dark_button" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#111"/>
            <stop offset="0.5" stop-color="#333"/>
            <stop offset="1" stop-color="#111"/>
        </linearGradient>        
        <linearGradient id="__gradient_mlib_dark_gray_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#111"/>
            <stop offset="0.5" stop-color="#333"/>
            <stop offset="1" stop-color="#111"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_dark_gray_h0" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#333"/>
            <stop offset="0.5" stop-color="#111"/>
            <stop offset="1" stop-color="#333"/>
        </linearGradient>        
        <radialGradient id="__gradient_mlib_dark_gray_c">
		<stop  offset="0" style="stop-color:#111"/>
		<stop  offset="1" style="stop-color:#333"/>
	</radialGradient>    
        
        <!-- light blue -->
        <linearGradient id="__gradient_mlib_light_blue_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#00a"/>
            <stop offset="0.5" stop-color="#00f"/>
            <stop offset="1" stop-color="#00a"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_light_blue_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#00a"/>
            <stop offset="0.5" stop-color="#00f"/>
            <stop offset="1" stop-color="#00a"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_light_blue_c">
		<stop  offset="0" style="stop-color:#00a"/>
		<stop  offset="1" style="stop-color:#00f"/>
	</radialGradient>
       
        <!-- midle blue -->
        <linearGradient id="__gradient_mlib_midle_blue_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#008"/>
            <stop offset="0.5" stop-color="#00a"/>
            <stop offset="1" stop-color="#008"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_blue_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#008"/>
            <stop offset="0.5" stop-color="#00a"/>
            <stop offset="1" stop-color="#008"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_midle_blue_c">
		<stop  offset="0" style="stop-color:#008"/>
		<stop  offset="1" style="stop-color:#00a"/>
	</radialGradient>
        
        <!-- dark blue -->
        <linearGradient id="__gradient_mlib_dark_blue_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#001"/>
            <stop offset="0.5" stop-color="#003"/>
            <stop offset="1" stop-color="#001"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_dark_blue_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#001"/>
            <stop offset="0.5" stop-color="#003"/>
            <stop offset="1" stop-color="#001"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_dark_blue_c">
		<stop  offset="0" style="stop-color:#001"/>
		<stop  offset="1" style="stop-color:#003"/>
	</radialGradient>  
        
        <!-- light green -->
        <linearGradient id="__gradient_mlib_light_green_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#0a0"/>
            <stop offset="0.5" stop-color="#0f0"/>
            <stop offset="1" stop-color="#0a0"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_light_green_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#0a0"/>
            <stop offset="0.5" stop-color="#0f0"/>
            <stop offset="1" stop-color="#0a0"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_light_green_c">
		<stop  offset="0" style="stop-color:#0a0"/>
		<stop  offset="1" style="stop-color:#0f0"/>
	</radialGradient>
       
        <!-- midle green -->
        <linearGradient id="__gradient_mlib_midle_green_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#080"/>
            <stop offset="0.5" stop-color="#0a0"/>
            <stop offset="1" stop-color="#080"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_green_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#080"/>
            <stop offset="0.5" stop-color="#0a0"/>
            <stop offset="1" stop-color="#080"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_green_ho" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#0a0"/>
            <stop offset="0.5" stop-color="#080"/>
            <stop offset="1" stop-color="#0a0"/>
        </linearGradient>        
        <radialGradient id="__gradient_mlib_midle_green_c">
		<stop  offset="0" style="stop-color:#080"/>
		<stop  offset="1" style="stop-color:#0a0"/>
	</radialGradient>
        
        <!-- dark green -->
        <linearGradient id="__gradient_mlib_dark_green_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#010"/>
            <stop offset="0.5" stop-color="#030"/>
            <stop offset="1" stop-color="#010"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_dark_green_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#010"/>
            <stop offset="0.5" stop-color="#030"/>
            <stop offset="1" stop-color="#010"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_dark_green_c">
		<stop  offset="0" style="stop-color:#010"/>
		<stop  offset="1" style="stop-color:#030"/>
	</radialGradient> 
        
      <!-- light red -->
        <linearGradient id="__gradient_mlib_light_red_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#a00"/>
            <stop offset="0.5" stop-color="#f00"/>
            <stop offset="1" stop-color="#a00"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_light_red_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#a00"/>
            <stop offset="0.5" stop-color="#f00"/>
            <stop offset="1" stop-color="#a00"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_light_red_c">
		<stop  offset="0" style="stop-color:#a00"/>
		<stop  offset="1" style="stop-color:#f00"/>
	</radialGradient>
       
        <!-- midle red -->
        <linearGradient id="__gradient_mlib_midle_red_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#800"/>
            <stop offset="0.5" stop-color="#a00"/>
            <stop offset="1" stop-color="#800"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_red_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#800"/>
            <stop offset="0.5" stop-color="#a00"/>
            <stop offset="1" stop-color="#800"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_midle_red_ho" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#a00"/>
            <stop offset="0.5" stop-color="#800"/>
            <stop offset="1" stop-color="#a00"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_midle_red_c">
		<stop  offset="0" style="stop-color:#800"/>
		<stop  offset="1" style="stop-color:#a00"/>
	</radialGradient>
        
        <!-- dark red -->
        <linearGradient id="__gradient_mlib_dark_red_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#100"/>
            <stop offset="0.5" stop-color="#300"/>
            <stop offset="1" stop-color="#100"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_dark_red_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#100"/>
            <stop offset="0.5" stop-color="#300"/>
            <stop offset="1" stop-color="#100"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_dark_red_c">
		<stop  offset="0" style="stop-color:#100"/>
		<stop  offset="1" style="stop-color:#300"/>
	</radialGradient>
        
        <!-- gaz -->
        <linearGradient id="__gradient_mlib_gaz_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#880"/>
            <stop offset="0.5" stop-color="#dd0"/>
            <stop offset="1" stop-color="#880"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_gaz_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#dd0"/>
            <stop offset="0.5" stop-color="#880"/>
            <stop offset="1" stop-color="#dd0"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_gaz_c">
		<stop  offset="0" style="stop-color:#880"/>
		<stop  offset="1" style="stop-color:#dd0"/>
	</radialGradient>  
        
        <!-- air -->
        <linearGradient id="__gradient_mlib_air_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#028"/>
            <stop offset="0.5" stop-color="#04b"/>
            <stop offset="1" stop-color="#028"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_air_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#04b"/>
            <stop offset="0.5" stop-color="#028"/>
            <stop offset="1" stop-color="#04b"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_air_c">
		<stop  offset="0" style="stop-color:#028"/>
		<stop  offset="1" style="stop-color:#04b"/>
	</radialGradient>
        
        <!-- water -->
        <linearGradient id="__gradient_mlib_water_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#093"/>
            <stop offset="0.5" stop-color="#0c5"/>
            <stop offset="1" stop-color="#093"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_water_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#0c5"/>
            <stop offset="0.5" stop-color="#093"/>
            <stop offset="1" stop-color="#0c5"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_water_c">
		<stop  offset="0" style="stop-color:#093"/>
		<stop  offset="1" style="stop-color:#0c5"/>
	</radialGradient>  
        
        <!-- smoke -->
        <linearGradient id="__gradient_mlib_smoke_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#999"/>
            <stop offset="0.5" stop-color="#ccc"/>
            <stop offset="1" stop-color="#999"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_smoke_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#ccc"/>
            <stop offset="0.5" stop-color="#999"/>
            <stop offset="1" stop-color="#ccc"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_smoke_c">
		<stop  offset="0" style="stop-color:#999"/>
		<stop  offset="1" style="stop-color:#ccc"/>
	</radialGradient> 
        
        <!-- vapor -->
        <linearGradient id="__gradient_mlib_vapor_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#a33"/>
            <stop offset="0.5" stop-color="#d55"/>
            <stop offset="1" stop-color="#a33"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_vapor_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#d55"/>
            <stop offset="0.5" stop-color="#a33"/>
            <stop offset="1" stop-color="#d55"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_vapor_c">
		<stop  offset="0" style="stop-color:#a33"/>
		<stop  offset="1" style="stop-color:#d55"/>
	</radialGradient>
        
        <!-- stream -->
        <linearGradient id="__gradient_mlib_stream_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#c3c"/>
            <stop offset="0.5" stop-color="#f0f"/>
            <stop offset="1" stop-color="#c3c"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_stream_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#f0f"/>
            <stop offset="0.5" stop-color="#c3c"/>
            <stop offset="1" stop-color="#f0f"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_stream_c">
		<stop  offset="0" style="stop-color:#c3c"/>
		<stop  offset="1" style="stop-color:#f0f"/>
	</radialGradient> 
        
        <!-- oil -->
        <linearGradient id="__gradient_mlib_oil_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#c63"/>
            <stop offset="0.5" stop-color="#f85"/>
            <stop offset="1" stop-color="#c63"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_oil_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#f85"/>
            <stop offset="0.5" stop-color="#c63"/>
            <stop offset="1" stop-color="#f85"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_oil_c">
		<stop  offset="0" style="stop-color:#c63"/>
		<stop  offset="1" style="stop-color:#f85"/>
	</radialGradient>           
        
        <!-- notice -->
        <linearGradient id="__gradient_mlib_notice_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#aa0"/>
            <stop offset="0.5" stop-color="#ff0"/>
            <stop offset="1" stop-color="#aa0"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_notice_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#ff0"/>
            <stop offset="0.5" stop-color="#aa0"/>
            <stop offset="1" stop-color="#ff0"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_notice_c">
		<stop  offset="0" style="stop-color:#aa0"/>
		<stop  offset="1" style="stop-color:#ff0"/>
	</radialGradient> 
        
        <!-- alarm -->
        <linearGradient id="__gradient_mlib_alarm_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#a92"/>
            <stop offset="0.5" stop-color="#f92"/>
            <stop offset="1" stop-color="#a92"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_alarm_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#f92"/>
            <stop offset="0.5" stop-color="#a92"/>
            <stop offset="1" stop-color="#f92"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_alarm_c">
		<stop  offset="0" style="stop-color:#a92"/>
		<stop  offset="1" style="stop-color:#f92"/>
	</radialGradient>
        
        <!-- accident -->
        <linearGradient id="__gradient_mlib_accident_v" y2="100%" x1="0%" y1="100%" x2="100%">
            <stop offset="0" stop-color="#a00"/>
            <stop offset="0.5" stop-color="#f00"/>
            <stop offset="1" stop-color="#a00"/>
        </linearGradient>
        <linearGradient id="__gradient_mlib_accident_h" x2="100%" y2="100%" x1="100%" y1="0%">
            <stop offset="0" stop-color="#f00"/>
            <stop offset="0.5" stop-color="#a00"/>
            <stop offset="1" stop-color="#f00"/>
        </linearGradient>
        <radialGradient id="__gradient_mlib_accident_c">
		<stop  offset="0" style="stop-color:#a00"/>
		<stop  offset="1" style="stop-color:#f00"/>
	</radialGradient> 

        
        
         <style type="text/css">           
        <!--
          light_gray
          midle_gray
          dark_gray
          light_blue
          midle_blue
          dark_blue 
          light_green
          midle_green
          dark_green          
          light_red
          midle_red
          dark_red  
          gaz
          water
          air
          vapor
          oil
          stream
          smoke
          notice
          alarm
          accident
        -->
        
        <!-- light gray -->
        .__fill_mlib_class_light_gray_v {
                fill : url(#__gradient_mlib_light_gray_v);}
        .__fill_mlib_class_light_gray_h {
                fill : url(#__gradient_mlib_light_gray_h);}  
        .__fill_mlib_class_light_gray_c {
                fill : url(#__gradient_mlib_light_gray_c);}  
                
                
        <!-- midle gray -->                
        .__fill_mlib_class_midle_gray_v {
                fill : url(#__gradient_mlib_midle_gray_v);}
        .__fill_mlib_class_midle_gray_h {
                fill : url(#__gradient_mlib_midle_gray_h);}  
        .__fill_mlib_class_midle_gray_c {
                fill : url(#__gradient_mlib_midle_gray_c);}
                
                
        <!-- dark gray -->                  
        .__fill_mlib_class_dark_gray_v {
                fill : url(#__gradient_mlib_dark_gray_v);}
        .__fill_mlib_class_dark_fill {
                fill : url(#__gradient_mlib_dark_fill);}    
        .__fill_mlib_class_dark_button {
                fill : url(#__gradient_mlib_dark_button);}                   
        .__fill_mlib_class_dark_gray_h {
                fill : url(#__gradient_mlib_dark_gray_h);}  
        .__fill_mlib_class_dark_gray_c {
                fill : url(#__gradient_mlib_dark_gray_c);}         
                
                
        <!-- light blue -->
        .__fill_mlib_class_light_blue_v {
                fill : url(#__gradient_mlib_light_blue_v);}
        .__fill_mlib_class_light_blue_h {
                fill : url(#__gradient_mlib_light_blue_h);}  
        .__fill_mlib_class_light_blue_c {
                fill : url(#__gradient_mlib_light_blue_c);}  
                
                
        <!-- midle blue -->                
        .__fill_mlib_class_midle_blue_v {
                fill : url(#__gradient_mlib_midle_blue_v);}
        .__fill_mlib_class_midle_blue_h {
                fill : url(#__gradient_mlib_midle_blue_h);}  
        .__fill_mlib_class_midle_blue_c {
                fill : url(#__gradient_mlib_midle_blue_c);}
                
                
        <!-- dark blue -->                  
        .__fill_mlib_class_dark_blue_v {
                fill : url(#__gradient_mlib_dark_blue_v);}
        .__fill_mlib_class_dark_blue_h {
                fill : url(#__gradient_mlib_dark_blue_h);}  
        .__fill_mlib_class_dark_blue_c {
                fill : url(#__gradient_mlib_dark_blue_c);}
                
        <!-- light green -->
        .__fill_mlib_class_light_green_v {
                fill : url(#__gradient_mlib_light_green_v);}
        .__fill_mlib_class_light_green_h {
                fill : url(#__gradient_mlib_light_green_h);}  
        .__fill_mlib_class_light_green_c {
                fill : url(#__gradient_mlib_light_green_c);}  
                
                
        <!-- midle green -->                
        .__fill_mlib_class_midle_green_v {
                fill : url(#__gradient_mlib_midle_green_v);}
        .__fill_mlib_class_midle_green_h {
                fill : url(#__gradient_mlib_midle_green_h);}  
        .__fill_mlib_class_midle_green_c {
                fill : url(#__gradient_mlib_midle_green_c);}
                
                
        <!-- dark green -->                  
        .__fill_mlib_class_dark_green_v {
                fill : url(#__gradient_mlib_dark_green_v);}
        .__fill_mlib_class_dark_green_h {
                fill : url(#__gradient_mlib_dark_green_h);}  
        .__fill_mlib_class_dark_green_c {
                fill : url(#__gradient_mlib_dark_green_c);}   
                
        <!-- light red -->
        .__fill_mlib_class_light_red_v {
                fill : url(#__gradient_mlib_light_red_v);}
        .__fill_mlib_class_light_red_h {
                fill : url(#__gradient_mlib_light_red_h);}  
        .__fill_mlib_class_light_red_c {
                fill : url(#__gradient_mlib_light_red_c);}  
                
                
        <!-- midle red -->                
        .__fill_mlib_class_midle_red_v {
                fill : url(#__gradient_mlib_midle_red_v);}
        .__fill_mlib_class_midle_red_h {
                fill : url(#__gradient_mlib_midle_red_h);}  
        .__fill_mlib_class_midle_red_c {
                fill : url(#__gradient_mlib_midle_red_c);}
                
                
        <!-- dark red -->                  
        .__fill_mlib_class_dark_red_v {
                fill : url(#__gradient_mlib_dark_red_v);}
        .__fill_mlib_class_dark_red_h {
                fill : url(#__gradient_mlib_dark_red_h);}  
        .__fill_mlib_class_dark_red_c {
                fill : url(#__gradient_mlib_dark_red_c);}   
                
        <!-- gaz -->
        .__fill_mlib_class_gaz_v {
                fill : url(#__gradient_mlib_gaz_v);}
        .__fill_mlib_class_gaz_h {
                fill : url(#__gradient_mlib_gaz_h);}  
        .__fill_mlib_class_gaz_c {
                fill : url(#__gradient_mlib_gaz_c);}  
                
        <!-- air -->
        .__fill_mlib_class_air_v {
                fill : url(#__gradient_mlib_air_v);}
        .__fill_mlib_class_air_h {
                fill : url(#__gradient_mlib_air_h);}  
        .__fill_mlib_class_air_c {
                fill : url(#__gradient_mlib_air_c);} 
                
        <!-- water -->
        .__fill_mlib_class_water_v {
                fill : url(#__gradient_mlib_water_v);}
        .__fill_mlib_class_water_h {
                fill : url(#__gradient_mlib_water_h);}  
        .__fill_mlib_class_water_c {
                fill : url(#__gradient_mlib_water_c);}       
                
        <!-- vapor -->
        .__fill_mlib_class_vapor_v {
                fill : url(#__gradient_mlib_vapor_v);}
        .__fill_mlib_class_vapor_h {
                fill : url(#__gradient_mlib_vapor_h);}  
        .__fill_mlib_class_vapor_c {
                fill : url(#__gradient_mlib_vapor_c);} 
                
        <!-- oil -->
        .__fill_mlib_class_oil_v {
                fill : url(#__gradient_mlib_oil_v);}
        .__fill_mlib_class_oil_h {
                fill : url(#__gradient_mlib_oil_h);}  
        .__fill_mlib_class_oil_c {
                fill : url(#__gradient_mlib_oil_c);} 
                
        <!-- stream -->
        .__fill_mlib_class_stream_v {
                fill : url(#__gradient_mlib_stream_v);}
        .__fill_mlib_class_stream_h {
                fill : url(#__gradient_mlib_stream_h);}  
        .__fill_mlib_class_stream_c {
                fill : url(#__gradient_mlib_stream_c);}  
                
        <!-- smoke -->
        .__fill_mlib_class_smoke_v {
                fill : url(#__gradient_mlib_smoke_v);}
        .__fill_mlib_class_smoke_h {
                fill : url(#__gradient_mlib_smoke_h);}  
        .__fill_mlib_class_smoke_c {
                fill : url(#__gradient_mlib_smoke_c);}               
                
        <!-- notice -->
        .__fill_mlib_class_notice_v {
                fill : url(#__gradient_mlib_notice_v);}
        .__fill_mlib_class_notice_h {
                fill : url(#__gradient_mlib_notice_h);}  
        .__fill_mlib_class_notice_c {
                fill : url(#__gradient_mlib_notice_c);}  
                
        <!-- alarm -->
        .__fill_mlib_class_alarm_v {
                fill : url(#__gradient_mlib_alarm_v);}
        .__fill_mlib_class_alarm_h {
                fill : url(#__gradient_mlib_alarm_h);}  
        .__fill_mlib_class_alarm_c {
                fill : url(#__gradient_mlib_alarm_c);}  
                
        <!-- accident -->
        .__fill_mlib_class_accident_v {
                fill : url(#__gradient_mlib_accident_v);}
        .__fill_mlib_class_accident_h {
                fill : url(#__gradient_mlib_accident_h);}  
        .__fill_mlib_class_accident_c {
                fill : url(#__gradient_mlib_accident_c);} 
                
                
                
        <!--  armatura -->
        
         .__mlib_armatura[cursor="pointer"] {
                outline: 1px solid transparent;
                cursor: pointer;}
                
         .__mlib_armatura[cursor="pointer"]:hover {
                outline: 1px solid #40FF00;
                cursor: pointer;}
                               
         .__mlib_armatura {             
               cursor: none;}
                     
         .__mlib_armatura:hover {            
               cursor: none;}
                 
                    
         
         
         
         
        <!-- button  -->
                
        svg svg text.__mlib_button_default {         
                 font-weight: bold;
                 text-anchor: middle;
                 dominant-baseline: central; 
                 -webkit-user-select: none;}
                 
           
        svg[state="disable"] svg text.__mlib_button_default {            
                 font-weight: normal;}
           
        svg.__mlib_button_default > g > rect {
                cursor: pointer;}
          
        svg[state="disable"].__mlib_button_default > g > rect {
                cursor: default;}
          
        svg.__mlib_button_default  > g  > rect {
                fill: transparent;}
                
        svg[state="off"].__mlib_button_default >   rect {        
                stroke: #555;
                stroke-width: 1;}   
                    
        svg[state="off"].__mlib_button_default:hover >  rect {         
                stroke:  #333;
                stroke-width: 1;}                  
                
        svg[state="disable"].__mlib_button_default >  rect , svg[state="disable"].__mlib_button_default:hover >  rect:hover , svg[state="disable"].__mlib_button_default >  rect:active {
                 stroke-width: 0;
                 stroke: none;}  
                 
        svg[state="disable"].__mlib_button_default > rect , svg[state="disable"].__mlib_button_default:hover > rect , svg[state="disable"].__mlib_button_default:active > rect {
                -webkit-svg-shadow: 0px 0px 0px rgba(0, 0, 0, 0);}  
                
        svg.__mlib_button_default:hover > rect {               
                -webkit-svg-shadow: 3px 3px  3px rgba(0, 0, 0, 0.5);}
         
        svg.__mlib_button_default:active > rect{
                -webkit-svg-shadow: 0px 0px 0px rgba(0, 0, 0, 0);} 
                
 


        .__mlib__button_green {
                fill: url(#__gradient_mlib_midle_green_h);} 
            
        svg[state=""]:active > rect.__mlib__button_green {
                fill: url(#__gradient_mlib_midle_green_ho);}  
                 
        svg[state="off"] > rect.__mlib__button_green {
                fill: url(#__gradient_mlib_midle_gray_h);} 
                    
        svg[state="off"]:active > rect.__mlib__button_green {
                fill: url(#__gradient_mlib_midle_gray_h0);}               
           
        svg[state="disable"] > rect.__mlib__button_green ,
        svg[state="disable"]:hover > rect.__mlib__button_green ,
        svg[state="disable"]:active > rect.__mlib__button_green {
                 fill: url(#__gradient_mlib_dark_gray_h); }  




        .__mlib__button_red {
                fill: url(#__gradient_mlib_midle_red_h);}
            
        svg[state=""]:active > rect.__mlib__button_red {
                fill: url(#__gradient_mlib_midle_red_ho);}  
                 
        svg[state="off"] > rect.__mlib__button_red {
                fill: url(#__gradient_mlib_midle_red_h);} 
                    
        svg[state="off"]:active > rect.__mlib__button_red {
                fill: url(#__gradient_mlib_midle_red_h0);}               
           
        svg[state="disable"] > rect.__mlib__button_red ,
        svg[state="disable"]:hover > rect.__mlib__button_red ,
        svg[state="disable"]:active > rect.__mlib__button_red {
                 fill: url(#__gradient_mlib_dark_gray_h); }
                 
   

 
        .__mlib__button_custom {
                fill: url(#__fill_mlib_class_dark_button);} 
            
        svg[state=""]:active > rect.__mlib__button_custom {
                fill: url(#__gradient_mlib_dark_gray_h0);}  
                 
        svg[state="off"] > rect.__mlib__button_custom {
                fill: url(#__fill_mlib_class_dark_button);} 
                    
        svg[state="off"]:active > rect.__mlib__button_custom {
                fill: url(#__gradient_mlib_dark_gray_h0);}               
           
        svg[state="disable"] > rect.__mlib__button_custom ,
        svg[state="disable"]:hover > rect.__mlib__button_custom ,
        svg[state="disable"]:active > rect.__mlib__button_custom {
                 fill: url(#__gradient_mlib_midle_gray_h); }  
                 
                 
                 
        .__mlib__button_rg {
                fill: url(#__gradient_mlib_midle_red_h);} 
            
        svg[state=""]:active > rect.__mlib__button_rg {
                fill: url(#__gradient_mlib_midle_red_h0);}  
                 
        svg[state="off"] > rect.__mlib__button_rg {
                fill: url(#__gradient_mlib_midle_green_h);} 
                    
        svg[state="off"]:active > rect.__mlib__button_rg {
                fill: url(#__gradient_mlib_midle_green_ho);}               
           
        svg[state="disable"] > rect.__mlib__button_rg ,
        svg[state="disable"]:hover > rect.__mlib__button_rg ,
        svg[state="disable"]:active > rect.__mlib__button_rg {
                 fill: url(#__gradient_mlib_dark_gray_h); }
                 

        .__mlib__button_gr {
                fill: url(#__gradient_mlib_midle_green_h);} 
            
        svg[state=""]:active > rect.__mlib__button_gr {
                fill: url(#__gradient_mlib_midle_green_h0);}  
                 
        svg[state="off"] > rect.__mlib__button_gr {
                fill: url(#__gradient_mlib_midle_red_h);} 
                    
        svg[state="off"]:active > rect.__mlib__button_gr {
                fill: url(#__gradient_mlib_midle_red_ho);}               
           
        svg[state="disable"] > rect.__mlib__button_gr ,
        svg[state="disable"]:hover > rect.__mlib__button_gr ,
        svg[state="disable"]:active > rect.__mlib__button_gr {
                 fill: url(#__gradient_mlib_dark_gray_h); }
   
               
                
              
        
        
        </style>
             
          
     </xsl:template>     
    
    



</xsl:stylesheet>
