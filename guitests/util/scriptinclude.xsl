<xsl:stylesheet xmlns="http://www.w3.org/2000/svg" xmlns:mlib="http://dvnci/mlib" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:html="http://www.w3.org/TR/xhtml1" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" version="1.0">
    
    <xsl:template name="lib_script_include_file"> 
        <xsl:param name="file"/>
        <xsl:if test="not(normalize-space($file)='')">
            <script type="text/javascript">
                <xsl:attribute name="xlink:href">
                    <xsl:value-of select="$file"/>
                </xsl:attribute>    
            </script>
        </xsl:if>
    </xsl:template>    
        
    <xsl:template id="scriptlist" name="lib_script_include">
        <xsl:call-template name="lib_script_include_file">
            <xsl:with-param name="file"/>
        </xsl:call-template>          
            
        
        <xsl:call-template name="lib_script_include_file">
            <xsl:with-param name="file">script1.js</xsl:with-param>
        </xsl:call-template>

    </xsl:template>


</xsl:stylesheet>