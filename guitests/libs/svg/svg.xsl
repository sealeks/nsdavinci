<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:svg="http://www.w3.org/2000/svg"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
extension-element-prefixes="svg">
    
  

    <xsl:template name="svglib">
         
    </xsl:template>
    
      
    <xsl:template name="apply_svg_schema">    
        <xsl:attribute name="xsi:schemaLocation">
            <xsl:text>../libs/svg/svg.xsd</xsl:text>
        </xsl:attribute>  
    </xsl:template>
    
    
    <xsl:template name="apply_svg_cxcy">
        <xsl:attribute name="cx">
            <xsl:choose>
                <xsl:when test="(boolean(@x) and not(@x=''))">
                     <xsl:value-of select="@x"/>
                </xsl:when>
                <xsl:when test="(boolean(@cx) and not(@cx=''))">
                     <xsl:value-of select="@cx"/>
                </xsl:when>   
                <xsl:otherwise>
                <xsl:text>100</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>
        <xsl:attribute name="cy">
            <xsl:choose>
                <xsl:when test="(boolean(@y) and not(@y=''))">
                     <xsl:value-of select="@y"/>
                </xsl:when>
                <xsl:when test="(boolean(@cy) and not(@cy=''))">
                     <xsl:value-of select="@cy"/>
                </xsl:when>   
                <xsl:otherwise>
                <xsl:text>100</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>
    </xsl:template>
   
     
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
      svg circle

    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->
    
    

    

    <xsl:template match="//svg:circle"> 
        <circle>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_svg_schema"/>  
            <xsl:call-template name="apply_svg_cxcy"/>
            <xsl:attribute name="r">
                <xsl:value-of select="@r"/>
            </xsl:attribute>
            <xsl:attribute name="stroke-width">
                <xsl:value-of select="@stroke-width"/>
            </xsl:attribute>  
            <xsl:attribute name="stroke">
                <xsl:value-of select="@stroke"/>
            </xsl:attribute>  
            <xsl:attribute name="fill">
                <xsl:value-of select="@fill"/>
            </xsl:attribute>
            <xsl:attribute name="style">
                <xsl:value-of select="@style"/>
            </xsl:attribute> 
        </circle>     
    </xsl:template>
    
</xsl:stylesheet>
