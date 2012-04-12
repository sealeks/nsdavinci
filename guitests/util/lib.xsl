<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:xlink="http://www.w3.org/1999/xlink"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    
    <xsl:import href="libstyle.xsl"/>

    <xsl:include href="../libs/main/mainlib.xsl" xsi:schemaLocation="../libs/main/mainlib.xsd"/>
    <xsl:include href="../libs/svg/svg.xsl" xsi:schemaLocation="../libs/svg/svg.xsd"/>
    

    <xsl:output  method="xml" indent="yes"/>
    
    <xsl:template match="/" >
        <xsl:processing-instruction name="xml-stylesheet">href="../util/css/libs.css"</xsl:processing-instruction>
        <xsl:apply-templates select="/*"/>
    </xsl:template>

    <xsl:template match="/*[position()=1]" > 
        <xsl:copy>
        <xsl:apply-templates select="@*"/> 
        <script type="text/javascript" xlink:href="../util/js/libutil.js"></script>
        <script type="text/javascript" xlink:href="../util/js/designer.js"></script>
        <xsl:call-template name="includelib"/> 
        <xsl:call-template name="lib_svgstyle"/> 
        <xsl:apply-templates/>
        </xsl:copy>
    </xsl:template>
    

    <xsl:template name="includelib">       
        <xsl:call-template name="mainlib"/>     
    </xsl:template> 
    
    <xsl:template match="*|@*|text()">
        <xsl:element name="{local-name()}">
            <xsl:apply-templates select="*|@*|text()"/>
        </xsl:element>
    </xsl:template>
    

    <xsl:template match="@*">
        <xsl:copy>
            <xsl:apply-templates select="@*"/>
        </xsl:copy>
    </xsl:template>
    
    
    <xsl:template match="text()">
        <xsl:copy>
            <xsl:apply-templates select="text()"/>
        </xsl:copy>
    </xsl:template>
    
    
    
    <!-- main template  -->
    
    <xsl:template name="startcddata">
        <xsl:text disable-output-escaping="yes">&lt;![CDATA[</xsl:text>
    </xsl:template>  
    
    <xsl:template name="stopcddata">    
        <xsl:text disable-output-escaping="yes">]]&gt;</xsl:text>      
    </xsl:template>    
    
    <xsl:template name="apply_rect"> 
        <xsl:attribute name="x">
            <xsl:value-of select="@x"/>
        </xsl:attribute>
        <xsl:attribute name="y">
            <xsl:value-of select="@y"/>
        </xsl:attribute>
        <xsl:attribute name="height">
            <xsl:value-of select="@height"/>
        </xsl:attribute>
        <xsl:attribute name="width">
            <xsl:value-of select="@width"/>
        </xsl:attribute>
    </xsl:template>
    
    <xsl:template name="apply_xy"> 
        <xsl:attribute name="x">
            <xsl:value-of select="@x"/>
        </xsl:attribute>
        <xsl:attribute name="y">
            <xsl:value-of select="@y"/>
        </xsl:attribute>
    </xsl:template> 
    
    <xsl:template name="apply_0_0_width_height"> 
        <xsl:attribute name="x">
            <xsl:text>0</xsl:text>
        </xsl:attribute>
        <xsl:attribute name="y">
            <xsl:text>0</xsl:text>
        </xsl:attribute>
        <xsl:attribute name="height">
            <xsl:value-of select="@height"/>
        </xsl:attribute>
        <xsl:attribute name="width">
            <xsl:value-of select="@width"/>
        </xsl:attribute>
    </xsl:template>
    
    <xsl:template name="apply_rect_b2"> 
        <xsl:attribute name="x">
            <xsl:value-of select="@x + 2"/>
        </xsl:attribute>
        <xsl:attribute name="y">
            <xsl:value-of select="@y + 2"/>
        </xsl:attribute>
        <xsl:attribute name="height">
            <xsl:value-of select="@height  - 4"/>
        </xsl:attribute>
        <xsl:attribute name="width">
            <xsl:value-of select="@width - 4"/>
        </xsl:attribute>
    </xsl:template>
    
    <xsl:template name="apply_rect_b4"> 
        <xsl:attribute name="x">
            <xsl:value-of select="@x + 4"/>
        </xsl:attribute>
        <xsl:attribute name="y">
            <xsl:value-of select="@y + 4"/>
        </xsl:attribute>
        <xsl:attribute name="height">
            <xsl:value-of select="@height - 8"/>
        </xsl:attribute>
        <xsl:attribute name="width">
            <xsl:value-of select="@width - 8"/>
        </xsl:attribute>
    </xsl:template> 
    
    
    <xsl:template name="apply_id">    
        <xsl:attribute name="id">
            <xsl:value-of select="@id"/>
        </xsl:attribute>
    </xsl:template>    
    
   
    <xsl:template name="apply_cental_rotate">    
        <xsl:choose>
            <xsl:when test="boolean(@rotate) and not(normalize-space(@rotate)='')">
                <xsl:attribute name="transform">
                    <xsl:text>rotate(</xsl:text>
                    <xsl:value-of select="@rotate"/>
                    <xsl:text>,</xsl:text>
                    <xsl:value-of select="@x + @width div 2"/>
                    <xsl:text>,</xsl:text>
                    <xsl:value-of select="@y + @height div 2"/>
                    <xsl:text>)</xsl:text>
                </xsl:attribute>
            </xsl:when>
        </xsl:choose>
    </xsl:template>   
    
    
    <xsl:template name="apply_r">     
        <xsl:choose>
            <xsl:when test="boolean(@r) and not(normalize-space(@r)='')">
                <xsl:attribute name="rx">
                    <xsl:value-of select="@r"/>
                </xsl:attribute>
                <xsl:attribute name="ry">
                    <xsl:value-of select="@r"/>
                </xsl:attribute>   
            </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    
    <xsl:template name="apply_visible">     
        <xsl:choose>
            <xsl:when test="boolean(@visible) and not(normalize-space(@visible)='')">
                <xsl:attribute name="display">
                     <xsl:text> #{ ( </xsl:text>
                     <xsl:value-of select="@visible"/>
                     <xsl:text>) ? 'block' : 'none' } </xsl:text>
                </xsl:attribute>
            </xsl:when>
        </xsl:choose>
    </xsl:template> 
    

</xsl:stylesheet>
