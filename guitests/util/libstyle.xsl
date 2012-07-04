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
     
          
     </xsl:template>     
    
    



</xsl:stylesheet>
