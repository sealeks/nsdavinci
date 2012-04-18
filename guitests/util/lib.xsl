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
    
   <xsl:template name="apply_svg_g_visible_binding">        
        <xsl:choose>
            <xsl:when test="(boolean(@visible-binding) and not(normalize-space(@visible-binding)='')) ">
               <xsl:attribute name="style">
                 <xsl:text>#{ (</xsl:text>  
                 <xsl:value-of select="@visible-binding"/>
                 <xsl:text>) ? 'display: block;' : 'display: none;' :default display: block;}</xsl:text> 
               </xsl:attribute>
               <xsl:attribute name="dv-visible">
                   <xsl:text>true</xsl:text> 
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template>
    
    <xsl:template name="apply_svg_g_visible">        
        <xsl:choose>
            <xsl:when test="(boolean(@visible) and not(normalize-space(@visible)='')) ">
               <xsl:attribute name="style">
                 <xsl:text>#{ (</xsl:text>  
                 <xsl:value-of select="@visible"/>
                 <xsl:text>) ? 'display: block;' : 'display: none;' :default display: none;}</xsl:text> 
               </xsl:attribute>
               <xsl:attribute name="dv-visible">
                   <xsl:text>true</xsl:text> 
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template>
    
    <xsl:template name="apply_lib_onclick">        
        <xsl:choose>
            <xsl:when test="(boolean(@onclick) and not(normalize-space(@onclick)='')) ">
               <xsl:attribute name="onclick">
                   <xsl:value-of select="@onclick"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template>
    
    <xsl:template name="apply_lib_ondblclick">        
        <xsl:choose>
            <xsl:when test="(boolean(@ondblclick) and not(normalize-space(@ondblclick)='')) ">
               <xsl:attribute name="ondblclick">
                   <xsl:value-of select="@ondblclick"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template> 
    
    <xsl:template name="apply_lib_onmousemove">        
        <xsl:choose>
            <xsl:when test="(boolean(@onmousemove) and not(normalize-space(@onmousemove)='')) ">
               <xsl:attribute name="onmousemove">
                   <xsl:value-of select="@onmousemove"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template> 
    
    <xsl:template name="apply_lib_onmouseup">        
        <xsl:choose>
            <xsl:when test="(boolean(@onmouseup) and not(normalize-space(@onmouseup)='')) ">
               <xsl:attribute name="onmouseup">
                   <xsl:value-of select="@onmouseup"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template>
    
    <xsl:template name="apply_lib_onmousedown">        
        <xsl:choose>
            <xsl:when test="(boolean(@onmousedown) and not(normalize-space(@onmousedown)='')) ">
               <xsl:attribute name="onmousedown">
                   <xsl:value-of select="@onmousedown"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template> 
    
    <xsl:template name="apply_lib_onmouseout">        
        <xsl:choose>
            <xsl:when test="(boolean(@onmouseout) and not(normalize-space(@onmouseout)='')) ">
               <xsl:attribute name="onmouseout">
                   <xsl:value-of select="@onmouseout"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template> 
    
    <xsl:template name="apply_lib_onmouseover">        
        <xsl:choose>
            <xsl:when test="(boolean(@onmouseover) and not(normalize-space(@onmouseover)='')) ">
               <xsl:attribute name="onmouseover">
                   <xsl:value-of select="@onmouseover"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template>
    
    <xsl:template name="apply_lib_onmousewheel">        
        <xsl:choose>
            <xsl:when test="(boolean(@onmousewheel) and not(normalize-space(@onmousewheel)='')) ">
               <xsl:attribute name="onmousewheel">
                   <xsl:value-of select="@onmousewheel"/>
               </xsl:attribute>
            </xsl:when>   
        </xsl:choose>
    </xsl:template> 
    
    <xsl:template name="apply_lib_mouseevent"> 
        <xsl:call-template name="apply_lib_onclick"/> 
        <xsl:call-template name="apply_lib_ondblclick"/> 
        <xsl:call-template name="apply_lib_onmousemove"/> 
        <xsl:call-template name="apply_lib_onmouseup"/>
        <xsl:call-template name="apply_lib_onmousedown"/>
        <xsl:call-template name="apply_lib_onmouseout"/>
        <xsl:call-template name="apply_lib_onmouseover"/>
        <xsl:call-template name="apply_lib_onmousewheel"/>
    </xsl:template>    

</xsl:stylesheet>
