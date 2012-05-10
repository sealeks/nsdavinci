<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:xlink="http://www.w3.org/1999/xlink"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:exsl="http://xmlsoft.org/XSLT/namespace">
    

    <xsl:import href="scriptinclude.xsl"/>

    <xsl:output  method="xml" indent="yes"/>
    
    <xsl:template match="/*[position()=1]" > 
        <xsl:copy>
        <xsl:apply-templates select="@*"/> 
        <xsl:attribute name="version">
            <xsl:text>1.1</xsl:text>
        </xsl:attribute>
        <script type="text/javascript" xlink:href="../util/js/libutil.js"></script>
        <script type="text/javascript" xlink:href="../util/js/designer.js"></script>
        <xsl:call-template name="lib_script_include"/>
        <xsl:apply-templates/>
        </xsl:copy>
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
    
    
    
</xsl:stylesheet>
