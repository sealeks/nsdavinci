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
            <xsl:call-template name="apply_mlib_armatfilter"/>
            <xsl:call-template name="apply_mlib_style"/> 
        </defs>  
    </xsl:template>

    <xsl:template name="mailib_gradients">       
        <xsl:call-template name="apply_mlib_armatfilter"/>                
    </xsl:template>
    
    
    
   
   <xsl:template name="apply_mlib_armatfilter"> 
 
       <filter id="armat_filter1" filterUnits="userSpaceOnUse" x="0" y="0" width="1000" height="1000">
            <feGaussianBlur in="SourceAlpha" stdDeviation="40" result="blur"/>
            <!--feOffset in="blur" dx="0" dy="0" result="offsetBlur"/-->
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

        <filter id="armat_filter2" filterUnits="userSpaceOnUse" x="0" y="0" width="1000" height="1000">
            <feGaussianBlur in="SourceAlpha" stdDeviation="40" result="blur"/>
            <feOffset in="blur" dx="0" dy="0" result="offsetBlur"/>
            <feSpecularLighting in="blur" surfaceScale="5" specularConstant=".75" specularExponent="20" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="50000" y="100000" z="200000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint"/>
            <feMerge>
                <feMergeNode in="offsetBlur"/>
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>
        

        <filter id="tubefilter" >
            <feGaussianBlur in="SourceAlpha" stdDeviation="4" result="blur"/>
            <feOffset in="blur" dx="4" dy="4" result="offsetBlur"/>
            <feSpecularLighting in="blur" surfaceScale="5" specularConstant=".75" specularExponent="20" lighting-color="#bbbbbb" result="specOut">
                <fePointLight x="-5000" y="-10000" z="20000"/>
            </feSpecularLighting>
            <feComposite in="specOut" in2="SourceAlpha" operator="in" result="specOut"/>
            <feComposite in="SourceGraphic" in2="specOut" operator="arithmetic" k1="0" k2="1" k3="1" k4="0" result="litPaint">
            </feComposite>    
            <feMerge>
                <feMergeNode in="litPaint"/>
            </feMerge>
        </filter>


        
        
     </xsl:template>   
     
     
     <xsl:template name="apply_mlib_style"> 
    
          <linearGradient id="hgradientnone"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#F7F7F7"/>
		<stop  offset="0.5" style="stop-color:#D1D1D1"/>
		<stop  offset="1" style="stop-color:#ECECEC"/>
	</linearGradient>
        
        <linearGradient id="vgradientnone"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#F7F7F7"/>
		<stop  offset="0.5" style="stop-color:#D1D1D1"/>
		<stop  offset="1" style="stop-color:#ECECEC"/>
	</linearGradient>
        
        
        
        <linearGradient id="hgradientblack"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#666"/>
		<stop  offset="0.5" style="stop-color:#222"/>
		<stop  offset="1" style="stop-color:#666"/>
	</linearGradient>
        
        <linearGradient id="vgradientblack"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#666"/>
		<stop  offset="0.5" style="stop-color:#222"/>
		<stop  offset="1" style="stop-color:#666"/>
	</linearGradient>

	<linearGradient id="hgradientred"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AA0000"/>
		<stop  offset="0.5" style="stop-color:#FF0000"/>
		<stop  offset="1" style="stop-color:#AA0000"/>
	</linearGradient>
        
        <linearGradient id="vgradientred"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AA0000"/>
		<stop  offset="0.5" style="stop-color:#FF0000"/>
		<stop  offset="1" style="stop-color:#AA0000"/>
	</linearGradient>
        
        <linearGradient id="hgradientgreen"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#008800"/>
		<stop  offset="0.5" style="stop-color:#00BB00"/>
		<stop  offset="1" style="stop-color:#008800"/>
	</linearGradient>
        
        <linearGradient id="vgradientgreen"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#008800"/>
		<stop  offset="0.5" style="stop-color:#00BB00"/>
		<stop  offset="1" style="stop-color:#008800"/>
	</linearGradient>
        
        <linearGradient id="hgradientgaz"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FFFF44"/>
		<stop  offset="0.5" style="stop-color:#DDDD22"/>
		<stop  offset="1" style="stop-color:#FFFF44"/>
	</linearGradient>
        
        <linearGradient id="vgradientgaz"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FFFF44"/>
		<stop  offset="0.5" style="stop-color:#DDDD22"/>
		<stop  offset="1" style="stop-color:#FFFF44"/>
	</linearGradient> 
        
        <linearGradient id="hgradientwater"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55FFAA"/>
		<stop  offset="0.5" style="stop-color:#33CC99"/>
		<stop  offset="1" style="stop-color:#55FFAA"/>
	</linearGradient>
        
        <linearGradient id="vgradientwater"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55FFAA"/>
		<stop  offset="0.5" style="stop-color:#33CC99"/>
		<stop  offset="1" style="stop-color:#55FFAA"/>
	</linearGradient>
        
        <linearGradient id="hgradientair"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55BBFF"/>
		<stop  offset="0.5" style="stop-color:#3399FF"/>
		<stop  offset="1" style="stop-color:#55BBFF"/>
	</linearGradient>
        
        <linearGradient id="vgradientair"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#55BBFF"/>
		<stop  offset="0.5" style="stop-color:#3399FF"/>
		<stop  offset="1" style="stop-color:#55BBFF"/>
	</linearGradient>   
        
        <linearGradient id="hgradientoil"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FF8855"/>
		<stop  offset="0.5" style="stop-color:#CC6633"/>
		<stop  offset="1" style="stop-color:#FF8855"/>
	</linearGradient>
        
        <linearGradient id="vgradientoil"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#FF8855"/>
		<stop  offset="0.5" style="stop-color:#CC6633"/>
		<stop  offset="1" style="stop-color:#FF8855"/>
	</linearGradient> 
        
        <linearGradient id="hgradientstream"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#CC33CC"/>
		<stop  offset="0.5" style="stop-color:#FF00FF"/>
		<stop  offset="1" style="stop-color:#CC33CC"/>
	</linearGradient>
        
        <linearGradient id="vgradientstrem"  x1="0%" y1="100%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#CC33CC"/>
		<stop  offset="0.5" style="stop-color:#FF00FF"/>
		<stop  offset="1" style="stop-color:#CC33CC"/>
	</linearGradient> 
        
        <linearGradient id="gradientonbutton"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#AA0000"/>
		<stop  offset="0.5" style="stop-color:#FF0000"/>
		<stop  offset="1" style="stop-color:#AA0000"/>
	</linearGradient>
        
        <linearGradient id="gradientoffbutton"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#00AA00"/>
		<stop  offset="0.5" style="stop-color:#007700"/>
		<stop  offset="1" style="stop-color:#00AA00"/>
	</linearGradient>
        
        <linearGradient id="gradientdisablebutton"  x1="100%" y1="0%" x2="100%" y2="100%">
		<stop  offset="0" style="stop-color:#F7F7F7"/>
		<stop  offset="0.5" style="stop-color:#D1D1D1"/>
		<stop  offset="1" style="stop-color:#ECECEC"/>
	</linearGradient>           
        
    
     </xsl:template>     
    
    



</xsl:stylesheet>
