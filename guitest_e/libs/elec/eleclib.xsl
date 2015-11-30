<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:elib="http://dvnci/elib"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:exsl="http://xmlsoft.org/XSLT/namespace">
    


    <xsl:template name="eleclib">  
        <script type="text/javascript" xlink:href="../libs/elec/js/eleclib.js"></script>   
        <script type="text/javascript" xlink:href="../util/js_ext/jquery/jquery.min.js"></script>
        <script type="text/javascript" xlink:href="../util/js_ext/hightchart/highcharts.js"></script>
        
    </xsl:template>
    
      
    <xsl:template name="apply_elib_schema">    
        <!--xsl:attribute name="xsi:schemaLocation">
            <xsl:text>../libs/elec/maillib.xsd</xsl:text>
        </xsl:attribute-->  
    </xsl:template>
    
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
          kU800
          kU500
          air
          vapor
          oil
          stream
          smoke
          notice
          alarm
          accident
          dark_fill
          dark_button
        -->  
    <xsl:template name="elib_gradient_select">
        <xsl:param name="invir"/>
        <xsl:param name="gradtype"/>
        <xsl:choose> 
            <xsl:when test="normalize-space($invir)='light_gray'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_light_gray_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_light_gray_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_light_gray_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>

            <xsl:when test="normalize-space($invir)='kUlow'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kUlow_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kUlow_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kUlow_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>  
            
            <xsl:when test="normalize-space($invir)='kU800'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU800_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU800_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU800_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>   
            
            <xsl:when test="normalize-space($invir)='kU500'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU500_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU500_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU500_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>  
            
            <xsl:when test="normalize-space($invir)='kU400'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU400_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU400_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU400_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when> 
            
            <xsl:when test="normalize-space($invir)='kU330'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU330_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU330_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU330_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>  
            
            <xsl:when test="normalize-space($invir)='kU220'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU220_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU220_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU220_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when> 
            
            <xsl:when test="normalize-space($invir)='kU150'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU150_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU150_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU150_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>        
            
             <xsl:when test="normalize-space($invir)='kU110'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_kU110_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_kU110_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_kU110_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>   
            
            <xsl:when test="normalize-space($invir)='notice'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_notice_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_notice_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_notice_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>  
            
            <xsl:when test="normalize-space($invir)='alarm'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_alarm_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_alarm_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_alarm_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>    
            
            <xsl:when test="normalize-space($invir)='accident'">
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_accident_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_accident_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_accident_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>    
            
           <xsl:when test="normalize-space($invir)='dark_fill'">
                 
                        <xsl:text>__fill_elib_class_dark_fill</xsl:text>
               
            </xsl:when>  
            
           <xsl:when test="normalize-space($invir)='dark_button'">
                 
                      <xsl:text>__fill_elib_class_dark_button</xsl:text>
                
            </xsl:when>             
            
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="($gradtype='tb')">
                        <xsl:text>__fill_elib_class_dark_blue_v</xsl:text>
                    </xsl:when>
                    <xsl:when test="($gradtype='c')">
                        <xsl:text>__fill_elib_class_dark_blue_c</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__fill_elib_class_dark_blue_h</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:otherwise>        
        </xsl:choose>   
    </xsl:template>    
    
    
    <!--
    
    config popup
    
    -->
    

    
    
    <xsl:template name="elib_config_popup_row">
        <xsl:param name="token"/>
        <xsl:param name="hdr"/>
        <xsl:param name="frmt"/>
        <xsl:param name="depth"/> 
        
        <xsl:variable name="format">
            <xsl:choose> 
                <xsl:when test="not(normalize-space($frmt))=''">
                    <xsl:value-of select="$frmt"/>
                </xsl:when>  
                <xsl:otherwise>
                    <xsl:text>%3.2f</xsl:text>
                </xsl:otherwise>        
            </xsl:choose>            
        </xsl:variable> 
        
        <xsl:variable name="header">
            <xsl:choose> 
                <xsl:when test="normalize-space($hdr)=''">
                    <xsl:value-of select="$hdr"/>
                </xsl:when>  
                <xsl:otherwise>
                    <xsl:text>token</xsl:text>
                </xsl:otherwise>        
            </xsl:choose>            
        </xsl:variable>         
        
        <elib:sensor x="5"  height="22" width="156" stroke="#eee" stroke-width="1" r="4"  color1="#111"   alighn="left" fontcolor="yellow" fontstyle="font-size: 11">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_popup_config_rowheader</xsl:text>
                <xsl:value-of select="$depth"/>
            </xsl:attribute>
            <xsl:attribute name="caption">
                <xsl:value-of select="$hdr"/>
            </xsl:attribute>
            <xsl:attribute name="y">
                <xsl:value-of select="30 + ($depth -1) * 24"/>
            </xsl:attribute>  
       </elib:sensor>
        <elib:sensor x="162"  height="22" width="82" stroke="#0e0" stroke-width="1" r="4"  color1="#001" caption="" alighn="right" fontcolor="#0e0" fontstyle="font-size: 11" sensorevent="valueedit">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_popup_config_setter</xsl:text>
                <xsl:value-of select="$depth"/>
            </xsl:attribute>
            <xsl:attribute name="param">
                <xsl:value-of select="$token"/>
            </xsl:attribute> 
            <xsl:attribute name="format">
                <xsl:value-of select="$format"/>
            </xsl:attribute>             
            <xsl:attribute name="y">
                <xsl:value-of select="30 + ($depth -1) * 24"/>
            </xsl:attribute>              
        </elib:sensor>
    </xsl:template>  
    
    
    <xsl:template name="elib_config_popup_split" >
        <xsl:param name="str" select="."/>
        <xsl:param name="hdrs"/>
        <xsl:param name="frmts"/>
        <xsl:param name="worddiv" select="','"/>
        <xsl:param name="depth"/>
        
        <xsl:variable name="depthvar">
            <xsl:choose> 
                <xsl:when test="normalize-space($depth)=''">
                    <xsl:text>0</xsl:text>
                </xsl:when>  
                <xsl:otherwise>
                    <xsl:value-of select="$depth + 1"/>
                </xsl:otherwise>        
            </xsl:choose> 
        </xsl:variable>
        
        <xsl:choose> 
            <xsl:when test="contains($str,$worddiv)">
                <xsl:call-template name="elib_config_popup_row">
                    <xsl:with-param name="token" select="substring-before($str, $worddiv)"/>
                    <xsl:with-param name="frmt" select="substring-before($frmts, $worddiv)"/>
                    <xsl:with-param name="hdr" select="substring-before($hdrs, $worddiv)"/>
                    <xsl:with-param name="depth" select="$depthvar"/>
                </xsl:call-template>
                <xsl:call-template name="elib_config_popup_split"> 
                    <xsl:with-param name="str" select="substring-after($str, $worddiv)"/>
                    <xsl:with-param name="frmts" select="substring-after($frmts, $worddiv)"/>
                    <xsl:with-param name="hdrs" select="substring-after($hdrs, $worddiv)"/>                    
                    <xsl:with-param name="worddiv" select="$worddiv"/>
                    <xsl:with-param name="depth" select="$depthvar"/>
                </xsl:call-template>
            </xsl:when>
 
            <xsl:otherwise>
                <xsl:call-template name="elib_config_popup_row">
                    <xsl:with-param name="token" select="$str"/>
                    <xsl:with-param name="frmt" select="$frmts"/>
                    <xsl:with-param name="hdr" select="$hdrs"/>
                    <xsl:with-param name="depth" select="$depthvar"/>
                </xsl:call-template>
            </xsl:otherwise>
 
        </xsl:choose>
    </xsl:template>
      
    
    <xsl:template name="elib_config_popup">
        <xsl:param name="header"/>
        <xsl:choose>
            <xsl:when test="not(normalize-space(@config)='')"> 
            
                <xsl:variable name="headervar">
                    <xsl:choose>
                        <xsl:when test="not(normalize-space($header)='')">
                            <xsl:value-of select="$header"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>Настройки</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>
                </xsl:variable>  
                
                <defs>
                    <script type="text/javascript">
                        
                        <xsl:text>if ((window.$$editable) &#38;&#38; (!$$editable())) { document.getElementById('</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>').addEventListener('contextmenu' ,function (ev) {
                        if (eleclib.check_click(this, event)) {  
                            eleclib.config_click(eleclib.check_click(this));
                            event.stopPropagation();
                            event.preventDefault();}});} </xsl:text>                    
                    </script>
                    <svg> 
                        <xsl:attribute name="id">
                            <xsl:value-of select="@id"/>
                            <xsl:text>_popup_config</xsl:text>
                        </xsl:attribute>                        
                
                        <xsl:variable name="popupbody">
                            <elib:sensor x="5" y="2" height="26" width="240" stroke="#ccc" stroke-width="1" r="4"  environment="midle_red"  alighn="center" fontcolor="#eee" fontstyle="font-size: 12">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_config_header</xsl:text>
                                </xsl:attribute>  
                                <xsl:attribute name="caption">
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@config-header)='')">
                                            <xsl:value-of select="@config-header"/>
                                        </xsl:when> 
                                        <xsl:otherwise>
                                            <xsl:choose>
                                                <xsl:when test="not(normalize-space(@param)='')">
                                                     <xsl:value-of select="$headervar"/>
                                                     <xsl:text> </xsl:text>
                                                     <xsl:value-of select="@param"/>
                                                </xsl:when>
                                                <xsl:otherwise>
                                                    <xsl:value-of select="$headervar"/>
                                                </xsl:otherwise>    
                                            </xsl:choose> 
                                        </xsl:otherwise>
                                    </xsl:choose>                                                                       
                                </xsl:attribute> 
                            </elib:sensor>
                            <xsl:call-template name="elib_config_popup_split">
                                <xsl:with-param name="str" select="@config"/>
                                <xsl:with-param name="hdrs" select="@config-headers"/>
                                <xsl:with-param name="frmts" select="@config-formats"/>
                                <xsl:with-param name="worddiv">,</xsl:with-param>
                                <xsl:with-param name="depth">0</xsl:with-param>
                            </xsl:call-template> 
                        </xsl:variable>
                        
                        <xsl:for-each select="exsl:node-set($popupbody)/*">
                            <xsl:choose>
                                <xsl:when test="local-name()='rect'">
                                    <xsl:call-template name="elib_button"/>
                                </xsl:when> 
                                <xsl:when test="local-name()='sensor'">
                                    <xsl:call-template name="elib_sensor"/>
                                </xsl:when>                         
                            </xsl:choose>
                        </xsl:for-each> 
                        
                    </svg> 
                </defs>
            </xsl:when>
        </xsl:choose>         
    </xsl:template>
    

     
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
 
 
        Компонент отображающий клапан или задвижку
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->
    
     <!--
    
    Отображение внешнего вида
    
    -->
 
 
    <xsl:template name="apply_elib_switchertype_breaker">    
        <!--rect x="200" y="200" height="50" width="600" stroke-width="0"/>
        <rect x="200" y="200" height="600" width="50" stroke-width="0"/>
        <rect x="200" y="800" height="50" width="600" stroke-width="0"/>
        <rect x="800" y="200" height="600" width="50" stroke-width="0"/--> 
        <!--rect x="200" y="200" width="600" height="600" stroke-width="50"/-->
        <!--path d="M 200,200 L 600,0 L 0,600 L -600, 0 L 0,-600z" stroke-width="30"/-->
        <!--path d="M 50 50 h 900 v 900 h -900 v -900 m 100 100 h 700 v 700 h -700 v -700z" stroke-width="none"/-->
        <rect x="50" y="50" height="900" width="900" stroke-width="none"/>
        <!--rect x="50" y="50" height="900" width="100" stroke-width="none"/>
        <rect x="50" y="850" height="100" width="900" stroke-width="none"/>
        <rect x="850" y="50" height="900" width="100" stroke-width="none"/-->        
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_isolator">    
        <!--circle cx="500" cy="500" r="300" stroke-width="20"/>
        <path d="M 400,450 L 400,550 L 550,550 L 550,600 L 650,500 L 550,400 L 550,450z" stroke-width="20"/-->
        <rect x="50" y="50" height="100" width="900" stroke-width="none"/>
        <rect x="50" y="850" height="100" width="900" stroke-width="none"/>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_ctransformator">    
        <circle cx="40" cy="50" r="35" fill="none" stroke-width="10"/>
        <line x1="70"  y1="30" x2="100" y2="30" stroke-width="10"/>
        <line x1="70" y1="70" x2="100" y2="70" stroke-width="10"/>
    </xsl:template>
    
    <xsl:template name="apply_elib_switchertype_fuse">    
        <path d="M 30,5 h 40 v 90 h -40 v -95"  fill="none" stroke-width="10"/>
        <path d="M 50,0 v 100" fill="none" stroke-width="10"/>    
    </xsl:template>   
    
    <xsl:template name="apply_elib_switchertype_generator">    
        <circle cx="50" cy="50" r="45" fill="none" stroke-width="10"/>
        <path d="M 20,50 a 15,15 0 1 1 30,0 M 50,50 a 15,15 1 0 0 30,0" fill="none" stroke-width="5"/>
    </xsl:template>
    
    <xsl:template name="apply_elib_switchertype_grounding">    
        <line x1="50" y1="0"   x2="50" y2="65" stroke-width="10"/>
        <line x1="40" y1="95" x2="60" y2="95" stroke-width="10"/>
        <line x1="25" y1="80" x2="75" y2="80" stroke-width="10"/>
        <line x1="10" y1="65" x2="90" y2="65" stroke-width="10"/> 
    </xsl:template>    
    
    <xsl:template name="apply_elib_switchertype_arrester">    
        <path d="M 35,82 h 30" fill="none" stroke-width="6"/>
        <path d="M 35,70 h 30" fill="none" stroke-width="6"/>    
        <path d="M 50,10 v 20" fill="none" stroke-width="6"/>  
        <path d="M 50,70 v -20" fill="none" stroke-width="6"/>
        <polygon points="47 20, 53 20, 50 30" fill="none" stroke-width="5"/>
        <polygon points="47 60, 53 60, 50 50" fill="none" stroke-width="5"/>    
        <path d="M 30,5 h 40 v 90 h -40 v -95"  fill="none" stroke-width="10"/>     
    </xsl:template>    
    
   
    <xsl:template name="apply_elib_switchertype_coil">    
        <path d="M 5,50 a 15,15 0 1 1 30,0 M 35,50 a 15,15 0 1 1 30,0 M 65,50 a 15,15 0 1 1 30,0" fill="none" stroke-width="5"/>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_compensator">    
        <path d="M 30,5 h 40 v 90 h -40 v -95"  fill="none" stroke-width="10"/>
        <line x1="50" y1="20"   x2="50" y2="40" stroke-width="6"/>
        <line x1="40" y1="40" x2="60" y2="40" stroke-width="6"/>
        <line x1="40" y1="60" x2="60" y2="60" stroke-width="6"/>
        <line x1="50" y1="60" x2="50" y2="80" stroke-width="6"/>     
    </xsl:template> 
    
    
    <xsl:template name="apply_elib_switchertype_condenser">    
        <line x1="50" y1="20"   x2="50" y2="40" stroke-width="10"/>
        <line x1="20" y1="40" x2="80" y2="40" stroke-width="10"/>
        <line x1="20" y1="60" x2="80" y2="60" stroke-width="10"/>
        <line x1="50" y1="60" x2="50" y2="80" stroke-width="10"/> 
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_kvpu">    
        <path d="M 30,5 h 40 v 90 h -40 v -95"  fill="none" stroke-width="10"/>
        <line x1="50" y1="65"   x2="50" y2="80" stroke-width="4"/>
        <line x1="50" y1="20"   x2="50" y2="60" stroke-width="4"/>
        <line x1="38" y1="65"   x2="62" y2="65" stroke-width="4"/>   
        <polygon points="46 50, 54 50, 50 56" fill="none" stroke-width="10"/>  
    </xsl:template>
    
    <xsl:template name="apply_elib_switchertype_reactor">    
        <path d="M50,95 v -45  h-45 a45,45 0 1,0 45,-45 " fill="none" stroke-width="10"/> 
    </xsl:template>    
    
    <xsl:template name="apply_elib_switchertype_suppressor">    
        <path d="M 30,5 h 40 v 90 h -40 v -95"  fill="none" stroke-width="10"/>
        <path d="M 86, 10 v 15 l -72, 50  v 15"  fill="none" stroke-width="6"/>    
    </xsl:template>    
    
    <xsl:template name="apply_elib_switchertype_synccondenser">    
        <circle cx="50" cy="50" r="45" fill="none" stroke-width="10"/>        
        <line x1="30"  y1="32" x2="70" y2="32" stroke-width="8"/>
        <line x1="30" y1="68" x2="70" y2="68" stroke-width="8"/> 
    </xsl:template>    
        
    <xsl:template name="apply_elib_switchertype_transformator1"> 
        <circle cx="50" cy="50" r="46" fill="none" stroke-width="8"/>           
    </xsl:template>            
        
    <xsl:template name="apply_elib_switchertype_transformator2">    
        <circle cx="50" cy="30" r="27" fill="none" stroke-width="6"/>
        <circle cx="50" cy="70" r="27" fill="none" stroke-width="6"/>        
    </xsl:template>      
    
    <xsl:template name="apply_elib_switchertype_transformator3">    
        <circle cx="50" cy="32" r="26" fill="none" stroke-width="5"/>
        <circle cx="29" cy="70" r="26" fill="none" stroke-width="5"/>
        <circle cx="71" cy="70" r="26" fill="none" stroke-width="5"/>         
    </xsl:template>            
        
    <xsl:template name="apply_elib_switchertype_transformator4">    
        <circle cx="50" cy="25" r="22" fill="none" stroke-width="5"/>
        <circle cx="50" cy="75" r="22" fill="none" stroke-width="5"/>
        <circle cy="50" cx="25" r="22" fill="none" stroke-width="5"/>
        <circle cy="50" cx="75" r="22" fill="none" stroke-width="5"/>           
    </xsl:template>         

    
    <xsl:template name="apply_elib_switchertype"> 
        <xsl:choose>                         
            <xsl:when test="boolean(@type) and not(normalize-space(@type)='')">                             
                <xsl:choose>
                    <xsl:when test="@type='generator'"> 
                        <xsl:call-template name="apply_elib_switchertype_generator"/>
                    </xsl:when>
                    <xsl:when test="@type='grounding'"> 
                        <xsl:call-template name="apply_elib_switchertype_grounding"/>
                    </xsl:when>                    
                    <xsl:when test="@type='arrester'"> 
                        <xsl:call-template name="apply_elib_switchertype_arrester"/>
                    </xsl:when>                  
                    <xsl:when test="@type='coil'"> 
                        <xsl:call-template name="apply_elib_switchertype_coil"/>
                    </xsl:when>
                    <xsl:when test="@type='compensator'">
                        <xsl:call-template name="apply_elib_switchertype_compensator"/> 
                    </xsl:when> 
                    <xsl:when test="@type='condenser'">
                        <xsl:call-template name="apply_elib_switchertype_condenser"/> 
                    </xsl:when>
                    <xsl:when test="@type='isolator'">
                        <xsl:call-template name="apply_elib_switchertype_isolator"/> 
                    </xsl:when> 
                    <xsl:when test="@type='ctransformator'">
                        <xsl:call-template name="apply_elib_switchertype_ctransformator"/> 
                    </xsl:when>
                    <xsl:when test="@type='fuse'">
                        <xsl:call-template name="apply_elib_switchertype_fuse"/> 
                    </xsl:when>                   
                    <xsl:when test="@type='kvpu'">
                        <xsl:call-template name="apply_elib_switchertype_kvpu"/> 
                    </xsl:when>
                    <xsl:when test="@type='reactor'">
                        <xsl:call-template name="apply_elib_switchertype_reactor"/> 
                    </xsl:when>              
                    <xsl:when test="@type='suppressor'">
                        <xsl:call-template name="apply_elib_switchertype_suppressor"/> 
                    </xsl:when>                     
                    <xsl:when test="@type='synccondenser'">
                        <xsl:call-template name="apply_elib_switchertype_synccondenser"/> 
                    </xsl:when>        
                    <xsl:when test="@type='transformator1'">
                        <xsl:call-template name="apply_elib_switchertype_transformator1"/> 
                    </xsl:when>                    
                    <xsl:when test="@type='transformator2'">
                        <xsl:call-template name="apply_elib_switchertype_transformator2"/> 
                    </xsl:when>        
                    <xsl:when test="@type='transformator3'">
                        <xsl:call-template name="apply_elib_switchertype_transformator3"/> 
                    </xsl:when>                    
                    <xsl:when test="@type='transformator4'">
                        <xsl:call-template name="apply_elib_switchertype_transformator4"/> 
                    </xsl:when>                                                          
                    <xsl:otherwise>
                        <xsl:call-template name="apply_elib_switchertype_breaker"/> 
                    </xsl:otherwise>                     
                </xsl:choose>
            </xsl:when> 
            <xsl:otherwise>
                <xsl:call-template name="apply_elib_switchertype_breaker"/> 
            </xsl:otherwise>                           
        </xsl:choose>    
    
    </xsl:template>
    
     <!--
    
    Отображение аттоибута cursor
    
    -->  
    
    
    <xsl:template name="apply_elib_switchertype_cursor_dsbl">
        <xsl:attribute name="cursor">
            <xsl:text>none</xsl:text>
        </xsl:attribute>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_cursor_checkstatevalid">
        <xsl:choose>                        
            <xsl:when test="not(normalize-space(@off)='') and not(normalize-space(@on)='')">
                <xsl:text>(!(</xsl:text>
                <xsl:value-of select="@on"/>
                <xsl:text>).valid  &#38;&#38; !(</xsl:text>
                <xsl:value-of select="@off"/>
                <xsl:text>).valid) ? 'none' : </xsl:text>
                               
            </xsl:when>
            <xsl:when test="boolean(@off) and not(normalize-space(@off)='')">
                <xsl:text>(!(</xsl:text>
                <xsl:value-of select="@off"/>
                <xsl:text>).valid) ? 'none' : </xsl:text>
            </xsl:when>
            <xsl:when test="boolean(@on) and not(normalize-space(@on)='')">
                <xsl:text>(!(</xsl:text>
                <xsl:value-of select="@on"/>
                <xsl:text>).valid) ? 'none' : </xsl:text>
            </xsl:when>
            <xsl:otherwise>
                <xsl:text></xsl:text>
            </xsl:otherwise>
        </xsl:choose> 
    </xsl:template>
    

    <xsl:template name="apply_elib_switchertype_cursor_autocontrol">
        <xsl:attribute name="cursor">
            <xsl:text>#{ </xsl:text>
            <xsl:call-template name="apply_elib_switchertype_cursor_checkstatevalid"/>
            <xsl:text> ( </xsl:text>
            <xsl:choose>                        
                <xsl:when test="(boolean(@local) and not(normalize-space(@local)=''))"> 
                    <xsl:value-of select="@local"/>
                    <xsl:text> ? 'none' : ( </xsl:text>
                    <xsl:value-of select="@auto"/>
                    <xsl:text> ? 'pointer' : 'pointer' </xsl:text>
                    <xsl:text> ) </xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@auto"/>
                    <xsl:text> ? 'pointer' : 'pointer' </xsl:text>
                    <xsl:text>  </xsl:text>                   
                </xsl:otherwise>
            </xsl:choose>        
            <xsl:text> ) :default none} </xsl:text>
        </xsl:attribute>
        <xsl:attribute name="autocontrol">
            <xsl:text>yes</xsl:text> 
        </xsl:attribute>    
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_cursor_auto">
        <xsl:attribute name="cursor">
            <xsl:text>#{ </xsl:text>
            <xsl:call-template name="apply_elib_switchertype_cursor_checkstatevalid"/>
            <xsl:text> ( </xsl:text>
            <xsl:choose>                        
                <xsl:when test="(boolean(@local) and not(normalize-space(@local)=''))"> 
                    <xsl:value-of select="@local"/>
                    <xsl:text> ? 'none' : ( </xsl:text>
                    <xsl:value-of select="@auto"/>
                    <xsl:text> ? 'none' : 'pointer' </xsl:text>
                    <xsl:text> ) </xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@auto"/>
                    <xsl:text> ? 'none' : 'pointer' </xsl:text>
                    <xsl:text>  </xsl:text>                   
                </xsl:otherwise>
            </xsl:choose>        
            <xsl:text> ) :default none} </xsl:text>
        </xsl:attribute>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_cursor_local">
        <xsl:attribute name="cursor">
            <xsl:text>#{ </xsl:text>
            <xsl:call-template name="apply_elib_switchertype_cursor_checkstatevalid"/>
            <xsl:text> ( </xsl:text>
            <xsl:choose>                        
                <xsl:when test="(boolean(@local) and not(normalize-space(@local)=''))"> 
                    <xsl:value-of select="@local"/>
                    <xsl:text> ? ('none' : 'pointer' )</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text> 'pointer'  </xsl:text>                  
                </xsl:otherwise>
            </xsl:choose>        
            <xsl:text> ) :default none} </xsl:text>
        </xsl:attribute>
    </xsl:template>
    
    
    
    <xsl:template name="apply_elib_switchertype_cursor">
        <xsl:choose>                        
            <xsl:when test="not(normalize-space(@off)='') or  not(normalize-space(@on)='')">
                <xsl:choose>                        
                    <xsl:when test=" not(normalize-space(@roff)='') or not(normalize-space(@ron)='') or not(normalize-space(@rauto)='')">
                        <xsl:choose>                        
                            <xsl:when test="not(normalize-space(@rauto)='') and  not(normalize-space(@auto)='')">
                                <xsl:call-template name="apply_elib_switchertype_cursor_autocontrol"/>
                            </xsl:when>
                            <xsl:when test="(boolean(@auto) and not(normalize-space(@auto)=''))">
                                <xsl:call-template name="apply_elib_switchertype_cursor_auto"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:call-template name="apply_elib_switchertype_cursor_local"/>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:call-template name="apply_elib_switchertype_cursor_dsbl"/>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="apply_elib_switchertype_cursor_dsbl"/>
            </xsl:otherwise>        
        </xsl:choose>    
    </xsl:template>
    
    
    <!--
    
    Описание логики состояния 
    
    -->  
    
    
    <xsl:template name="apply_elib_switchertype_state"> 
        <g class="none">
            <xsl:variable name="envir"> 
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@environment)='')"> 
                        <xsl:value-of select="@environment"/> 
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>__</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_armatclass</xsl:text>                        
                    </xsl:otherwise>
                </xsl:choose>                
            </xsl:variable>
            <xsl:choose>                              
                <xsl:when test="not(@filter='')">
                    <xsl:attribute name="filter">
                        <xsl:text>url(#filter_lib_armat1000)</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose> 
            <xsl:choose>                        
                <xsl:when test="(not(normalize-space(@on)=''))  and not(normalize-space(@off)='')"> 
                    <xsl:attribute name="class">
                        <xsl:text>non</xsl:text> 
                    </xsl:attribute>
                    <animate attributeName="class" attributeType="XML" fill="freeze" keyTimes="0;.5" dur="1000ms"  repeatCount="indefinite" calcMode="discrete"> 
                        <xsl:attribute name="values">
                            <xsl:text>#{ (!(</xsl:text>
                            <xsl:value-of select="@on"/>
                            <xsl:text>).valid &#38;&#38; !(</xsl:text>
                            <xsl:value-of select="@off"/>
                            <xsl:text>).valid) ? 'non;non;' : (</xsl:text>
                                
                            <xsl:value-of select="@on"/>
                            <xsl:text> &#38;&#38; !</xsl:text>
                            <xsl:value-of select="@off"/>
                            <xsl:text>) ? </xsl:text>
                                
                            <xsl:text>'on</xsl:text>
                            <xsl:value-of select="$envir"/>
                            <xsl:text>;on</xsl:text>
                            <xsl:value-of select="$envir"/>
                            <xsl:text>;'</xsl:text>
                                
                            <xsl:text> : (!</xsl:text>
                            <xsl:value-of select="@on"/>
                            <xsl:text> &#38;&#38; </xsl:text>
                            <xsl:value-of select="@off"/>
                            <xsl:text>) ? </xsl:text>
                                
                            <xsl:text>'off</xsl:text>
                            <!--xsl:value-of select="$envir"/--><xsl:text>kUNone</xsl:text>
                            <xsl:text>;off</xsl:text>
                            <!--xsl:value-of select="$envir"/--><xsl:text>kUNone</xsl:text>
                            <xsl:text>;' : </xsl:text>
                                
                                
                            <xsl:text>'on</xsl:text>
                            <xsl:value-of select="$envir"/>
                            <xsl:text>;off</xsl:text>
                            <!--xsl:value-of select="$envir"/--><xsl:text>kUNone</xsl:text>
                            <xsl:text>;'</xsl:text>
                                                                
                            <xsl:text> :default non;non;}</xsl:text>
                        </xsl:attribute>    
                    </animate>
                </xsl:when>
                <xsl:when test="boolean(@on) and not(normalize-space(@on)='')"> 
                    <xsl:attribute name="class">
                        <xsl:text>#{ !(</xsl:text>
                        <xsl:value-of select="@on"/>
                        <xsl:text>).valid  ? 'non'  : ((</xsl:text>
                        <xsl:value-of select="@on"/>
                        <xsl:text>)  ? 'on</xsl:text>
                        <xsl:value-of select="$envir"/>
                        <xsl:text>':  'off</xsl:text>
                        <!--xsl:value-of select="$envir"/--><xsl:text>kUNone</xsl:text>
                        <xsl:text>') :default non}</xsl:text> 
                    </xsl:attribute>
                </xsl:when>                    
                <xsl:when test="boolean(@off) and not(normalize-space(@off)='')"> 
                    <xsl:attribute name="class">
                        <xsl:text>#{ !(</xsl:text>
                        <xsl:value-of select="@off"/>
                        <xsl:text>).valid  ? 'non'  : ((</xsl:text>
                        <xsl:value-of select="@off"/>
                        <xsl:text>)  ? 'off</xsl:text>
                        <!--xsl:value-of select="$envir"/--><xsl:text>kUNone</xsl:text>
                        <xsl:text>':  'on</xsl:text>
                        <xsl:value-of select="$envir"/>
                        <xsl:text>') :default non}</xsl:text> 
                    </xsl:attribute>
                </xsl:when>
                <xsl:otherwise> 
                    <xsl:attribute name="class">
                        <xsl:text>on</xsl:text>
                        <xsl:value-of select="$envir"/>  
                    </xsl:attribute>
                </xsl:otherwise> 
            </xsl:choose>              
            <xsl:call-template name="apply_elib_switchertype"/> 
        </g>
    </xsl:template> 

    
    
    <!--
    
    Отображение состояния мест.
    
    -->
    
    <xsl:template name="apply_elib_switchertype_local_img">    
        <circle cx="150" cy="150" r="100" stroke-width="20"/>
        <path d="M 110,190 L 110,110 L 150,150 L 190,110 L 190,190" stroke-width="15"/>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_local">    
        <xsl:choose>
            <xsl:when test="not(normalize-space(@local)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@local"/>
                        <xsl:text> ? 'local'  : 'transparent' :default transparent }</xsl:text>
                    </xsl:attribute>                           
                    <xsl:call-template name="apply_elib_switchertype_local_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>  
    
    
    
    
    <!--
    
    Отображение состояния автоматический.
    
    -->
    
    <xsl:template name="apply_elib_switchertype_auto_img">    
        <circle cx="150" cy="150" r="100" stroke-width="20"/>
        <path d="M 110,190 L 150,110  L 190,190 M 140,150 L 160,150" stroke-width="15" fill="none"/>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_auto">    
        <xsl:choose>
            <xsl:when test="not(normalize-space(@auto)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@auto"/>
                        <xsl:text> ? 'autocontrol'  : 'transparent' :default transparent }</xsl:text>
                    </xsl:attribute>                              
                    <xsl:call-template name="apply_elib_switchertype_auto_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>   
    
    
    
    <!--
    
    Отображение состояния автоматический.
    
    -->
    
    <xsl:template name="apply_elib_switchertype_control_img">    
        <circle cx="850" cy="150" r="60" stroke-width="0"/>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_switchertype_control">    
        <xsl:choose>
            <xsl:when test="not(normalize-space(@control)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@control"/>
                        <xsl:text> ? 'oncheckcontrol'  : 'offcheckcontrol' :default oncheckcontrol }</xsl:text>
                    </xsl:attribute>                              
                    <xsl:call-template name="apply_elib_switchertype_control_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>      
    
    
    
    <!--
    
    Отображение сигналов открытия и закрытия
    
    -->
    
    
    <xsl:template name="apply_elib_switchertype_onsig">    
        <path d="M 450, 170 L 450,100 L 400,100 L 500,10  L 600,100 L 550,100 L 550,170z" stroke-width="0" stroke="none" fill="#0F0">
            <animate  attributeType="XML" attributeName="fill" values="#0F0;transparent;" keyTimes="0;.5" dur="500ms"  repeatCount="indefinite" calcMode="discrete"/>
        </path>
    </xsl:template>  
    
    <xsl:template name="apply_elib_switchertype_offsig">
        <path d="M 450, 10 L 450,80 L 400,80 L 500,170  L 600,80 L 550,80 L 550,10z" stroke-width="0" stroke="none" fill="#F00">
            <animate  attributeType="XML" attributeName="fill" values="transparent;#F00;" keyTimes="0;.5" dur="500ms"  repeatCount="indefinite" calcMode="discrete"/>
        </path>
    </xsl:template> 
    
    <xsl:template name="apply_elib_switchertype_sig">   
        <xsl:choose>                          
            <xsl:when test="not(normalize-space(@don)='')"> 
                <g>
                    <xsl:attribute name="style">
                        <xsl:choose>                          
                            <xsl:when test="not(normalize-space(@on)='')">                                               
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@don"/>
                                <xsl:text> &#38;&#38; !</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>)  ? 'display: block;' :  'display: none;'</xsl:text>
                                <xsl:text> :default display: none; }</xsl:text>                        
                            </xsl:when>
                            <xsl:otherwise>                         
                                <xsl:text>#{ </xsl:text>
                                <xsl:value-of select="@don"/>
                                <xsl:text>  ? 'display: block;' :  'display: none;'</xsl:text>
                                <xsl:text> :default display: none; }</xsl:text>                           
                            </xsl:otherwise>                         
                        </xsl:choose>
                    </xsl:attribute> 
                    <xsl:call-template name="apply_elib_switchertype_onsig"/>
                </g>
            </xsl:when>
        </xsl:choose> 
        <xsl:choose>
            <xsl:when test="not(normalize-space(@doff)='')"> 
                <g>
                    <xsl:attribute name="style">
                        <xsl:choose>                          
                            <xsl:when test="not(normalize-space(@off)='')">                                                 
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@doff"/>
                                <xsl:text> &#38;&#38; !</xsl:text>
                                <xsl:value-of select="@off"/>
                                <xsl:text>)  ? 'display: block;' :  'display: none;'</xsl:text>
                                <xsl:text> :default display: none; }</xsl:text>                             
                            </xsl:when>
                            <xsl:otherwise>                          
                                <xsl:text>#{ </xsl:text>
                                <xsl:value-of select="@doff"/>
                                <xsl:text>  ? 'display: block;' :  'display: none;'</xsl:text>
                                <xsl:text> :default display: none; }</xsl:text>                          
                            </xsl:otherwise>                            
                        </xsl:choose>
                    </xsl:attribute> 
                    <xsl:call-template name="apply_elib_switchertype_offsig"/>
                </g>                    
            </xsl:when>                    
        </xsl:choose>                                                   
    </xsl:template> 
    
    
    <!--
    
    Отображение аварийности
    
    -->
    
    <xsl:template name="apply_elib_switchertype_alarmstate">    
        <xsl:choose>                
            <xsl:when test="(boolean(@alarms) and not(normalize-space(@alarms)=''))">
                <g  class="accident" opacity="0.0">
                    <xsl:call-template name="apply_lib_alarm_class">
                        <xsl:with-param name="alarms" select="@alarms"/>
                        <xsl:with-param name="accident">accident</xsl:with-param>
                        <xsl:with-param name="alarm">alarm</xsl:with-param>
                        <xsl:with-param name="notice">notice</xsl:with-param>
                        <xsl:with-param name="default">accident</xsl:with-param>
                    </xsl:call-template>
                    <circle cx="500" cy="500" r="500"/>
                    <xsl:call-template name="apply_lib_alarm_animate">
                        <xsl:with-param name="attributeName">opacity</xsl:with-param>
                        <xsl:with-param name="attributeType">XML</xsl:with-param>
                        <xsl:with-param name="calcMode">linear</xsl:with-param>
                        <xsl:with-param name="alarms" select="@alarms"/>
                        <xsl:with-param name="on">1</xsl:with-param>
                        <xsl:with-param name="off">0</xsl:with-param> 
                    </xsl:call-template>                      
                </g>     
            </xsl:when>   
        </xsl:choose>  
    </xsl:template>
    
    
      <!--
    
    Установка функций управления
    
    -->
    
    
    <xsl:template name="apply_elib_switchertype_event"> 
        <xsl:choose>             
            <xsl:when test="boolean(@rauto) or boolean(@roff) or boolean(@ron)">  
                <xsl:attribute name="onclick">
                    <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                            <xsl:text>eleclib.switcher_popup(this, '</xsl:text>
                            <xsl:value-of select="@rauto"/>                                                    
                            <xsl:text>');};</xsl:text>
                </xsl:attribute>                   
            </xsl:when>               
        </xsl:choose>
    </xsl:template>  
    
    <!--
    
    формирование стиля
    
    -->    
    
    
    <xsl:template name="apply_elib_switchertype_style">
        <xsl:choose> 
            <xsl:when test="normalize-space(@environment)=''">
                <defs>
                    <style type="text/css">          
                        <xsl:choose>
                            <xsl:when test="boolean(@oncolor) and not(normalize-space(@oncolor)='')">
                                <xsl:variable name="offcolor">
                                    <xsl:choose>
                                        <xsl:when test="boolean(@offcolor) and not(normalize-space(@offcolor)='')">
                                            <xsl:value-of select="@offcolor"/>
                                        </xsl:when>
                                        <xsl:otherwise> 
                                            <xsl:text>black</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:variable>
                                <xsl:text> 
                   
                                </xsl:text>
                                <xsl:text>.on__</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_armatclass {</xsl:text>
                                <xsl:text>stroke: </xsl:text>
                                <xsl:value-of select="$offcolor"/>
                                <xsl:text>; </xsl:text>
                                <xsl:text>fill: </xsl:text>
                                <xsl:value-of select="@oncolor"/>
                                <xsl:text>;} 
                                </xsl:text>
                                <xsl:text> 
                  
                                </xsl:text>                  
                                <xsl:text>.off__</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_armatclass {</xsl:text>
                                <xsl:text>stroke: </xsl:text>
                                <xsl:value-of select="@oncolor"/>
                                <xsl:text>; </xsl:text>
                                <xsl:text>fill: </xsl:text>
                                <xsl:value-of select="$offcolor"/>
                                <xsl:text>;} 
                                </xsl:text>
                            </xsl:when>
                        </xsl:choose>   
            
            
                        <xsl:text> 
                        </xsl:text>
                    </style>  
                </defs>
            </xsl:when> 
        </xsl:choose> 
    </xsl:template>
    
    
   <xsl:template name="apply_elib_switchertype_popup">
       <defs>
           
            <xsl:variable name="typecontrol">
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@ron)='') and not(normalize-space(@roff)='')">
                        <xsl:text>onoff</xsl:text>
                    </xsl:when>
                    <xsl:when test="not(normalize-space(@ron)='')">
                        <xsl:text>on</xsl:text>
                    </xsl:when> 
                    <xsl:when test="not(normalize-space(@roff)='')">
                        <xsl:text>off</xsl:text>
                    </xsl:when>
                </xsl:choose>
            </xsl:variable>
                
            <xsl:variable name="disablecontrol">
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@auto)='')">
                        <xsl:text>onoff</xsl:text>
                    </xsl:when>
                </xsl:choose>
            </xsl:variable>
                
            <xsl:variable name="localcontrol">
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@rauto)='')">
                        <xsl:text>onoff</xsl:text>
                    </xsl:when>
                </xsl:choose>
            </xsl:variable> 
            
            <xsl:variable name="switcherkind"> 
                    <xsl:choose>
                        <xsl:when test="not(boolean(@type)) or (@type='isolator') or (@type='breaker') or (normalize-space(@type)='')">
                            <xsl:text>breaker</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>valve</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>        
            </xsl:variable>
            
            <xsl:variable name="oncaption">
                    <xsl:choose>
                        <xsl:when test="($switcherkind='breaker')">
                            <xsl:text>Пуск</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>Открыть</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>                
            </xsl:variable>
            
            <xsl:variable name="offcaption">
                    <xsl:choose>
                        <xsl:when test="($switcherkind='breaker')">
                            <xsl:text>Стоп</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>Закрыть</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>                
            </xsl:variable> 
            
            <xsl:variable name="stopcaption">
                    <xsl:choose>
                        <xsl:when test="($switcherkind='breaker')">
                            <xsl:text>Сброс</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>Стоп</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>                
            </xsl:variable>
            
            <xsl:variable name="statevalid">
                <xsl:choose>
                    <xsl:when test="$typecontrol='onoff'">
                        <xsl:value-of select="@ron"/>
                        <xsl:text> || </xsl:text>
                        <xsl:value-of select="@roff"/>
                    </xsl:when>
                    <xsl:when test="$typecontrol='on'">
                        <xsl:value-of select="@ron"/>
                    </xsl:when>
                    <xsl:when test="$typecontrol='off'">
                        <xsl:value-of select="@roff"/>
                    </xsl:when>                        
                </xsl:choose>    
            </xsl:variable>   
            
            <xsl:variable name="fontstyle">
                <xsl:text> font-size: 14 ; fill: white; </xsl:text>    
            </xsl:variable>             
            
            <xsl:variable name="fullvalid">
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@auto)='')  and not(normalize-space($statevalid)='')">
                        <xsl:text>(!(</xsl:text>
                        <xsl:value-of select="@auto"/>
                        <xsl:text> || </xsl:text>
                        <xsl:value-of select="$statevalid"/>
                        <xsl:text>).valid || </xsl:text>
                        <xsl:value-of select="@auto"/>
                        <xsl:text>)</xsl:text>
                    </xsl:when>
                    <xsl:when test="not(normalize-space($statevalid)='')">
                        <xsl:text>(!(</xsl:text>
                        <xsl:value-of select="$statevalid"/>
                        <xsl:text>).valid)</xsl:text>                      
                    </xsl:when>
                    <xsl:when test="not(normalize-space(@auto)='')">
                        <xsl:text>(!(</xsl:text>
                        <xsl:value-of select="@auto"/>
                        <xsl:text>).valid || </xsl:text>
                        <xsl:value-of select="@auto"/>
                        <xsl:text>)</xsl:text>
                    </xsl:when>                                       
                </xsl:choose>    
            </xsl:variable>            
            
            
            
           <svg width="100%" height="100%"> 
                <xsl:attribute name="id">
                    <xsl:value-of select="@id"/>
                    <xsl:text>_popup</xsl:text>
                </xsl:attribute>
                
                <xsl:attribute name="viewBox">
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@rauto)='')">
                            <xsl:text>0 0 200 250</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>0 0 200 200</xsl:text>
                        </xsl:otherwise>   
                    </xsl:choose>                                        
                </xsl:attribute>
                
                
                <xsl:variable name="popupbody">
                    <sensor x="5" y="10" width="190" height="80" environment="dark_gray" caption="{@header}" alighn="center" fontcolor="#eee" r="10" stroke="#eee" stroke-width="1">
                    </sensor>
                    <xsl:choose>
                        <xsl:when test="$typecontrol='onoff'">
                            <button x="5" y="100" width="190" height="30" param="{@ron}" kind="green" caption="{$oncaption}" disable="{$fullvalid}" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonon</xsl:text>
                                </xsl:attribute> 
                                <xsl:attribute name="param">
                                    <xsl:value-of select="@roff"/>
                                    <xsl:text> @ 0,</xsl:text>
                                    <xsl:value-of select="@ron"/>
                                    <xsl:text> @ 1</xsl:text>
                                </xsl:attribute>
                            </button>    
                            <button x="5" y="133" width="190" height="30" param="{@roff}" kind="custom" caption="{$stopcaption}" disable="{$fullvalid}" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonstop</xsl:text>
                                </xsl:attribute> 
                                <xsl:attribute name="param">
                                    <xsl:value-of select="@ron"/>
                                    <xsl:text> @ 0,</xsl:text>
                                    <xsl:value-of select="@roff"/>
                                    <xsl:text> @ 0</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="state">
                                    <xsl:value-of select="@ron"/>
                                    <xsl:text> || </xsl:text>
                                    <xsl:value-of select="@roff"/>
                                </xsl:attribute>                                
                            </button>
                            <button x="5" y="164" width="190" height="30" param="{@roff}" kind="red" caption="{$offcaption}" disable="{$fullvalid}" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonoff</xsl:text>
                                </xsl:attribute> 
                                <xsl:attribute name="param">
                                    <xsl:value-of select="@ron"/>
                                    <xsl:text> @ 0,</xsl:text>
                                    <xsl:value-of select="@roff"/>
                                    <xsl:text> @ 1</xsl:text>
                                </xsl:attribute>
                            </button>                            
                        </xsl:when> 
                        <xsl:when test="$typecontrol='on'">
                            <button x="5" y="100" width="190" height="90" param="{@ron}"  state="{@ron}" type="tumbler" fontstyle="font-size: 16; fill: #eee;" caption="{$oncaption}" oncaption="{$offcaption}" kind="gr" disable="{$fullvalid}" r="5">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button</xsl:text>
                                </xsl:attribute>                                
                            </button>
                        </xsl:when> 
                        <xsl:when test="$typecontrol='off'">
                            <button x="5" y="100" width="190" height="90" param="{@roff}" state="{@roff}" type="tumbler" fontstyle="font-size: 16;  fill: #eee;" caption="{$offcaption}" oncaption="{$oncaption}" kind="rg" disable="{$fullvalid}" r="5">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button</xsl:text>
                                </xsl:attribute>
                            </button>    
                        </xsl:when> 
                    </xsl:choose>
                    
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@rauto)='')">
                            <button x="5" y="205" width="190" height="40" param="{@rauto}" state="{@rauto}" type="tumbler" caption="В автомат" oncaption="В дист." kind="custom"  r="5">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button_local</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="disable">
                                    <xsl:text>!</xsl:text>
                                    <xsl:value-of select="@rauto"/>
                                    <xsl:text>.valid</xsl:text>
                                </xsl:attribute>
                            </button>   
                        </xsl:when>
                    </xsl:choose> 
                </xsl:variable> 
                    
                
                <xsl:for-each select="exsl:node-set($popupbody)/*">
                    <xsl:choose>
                        <xsl:when test="local-name()='button'">
                            <xsl:call-template name="elib_button"/>
                        </xsl:when>
                        <xsl:when test="local-name()='rect'">
                            <xsl:call-template name="elib_button"/>
                        </xsl:when> 
                        <xsl:when test="local-name()='sensor'">
                            <xsl:call-template name="elib_sensor"/>
                        </xsl:when>                         
                    </xsl:choose>
                </xsl:for-each>    
                
           </svg>               
       </defs>                   
   </xsl:template>       
    
    
    
    
  
  
        <!--
    
    Основной обработчик
    
    -->
      
    
    <xsl:template match="//elib:switcher" >   
        <g>       
        
            <xsl:attribute name="desc">
                <xsl:if test="boolean(@on)">
                    <xsl:value-of select="@on"/>
                </xsl:if>
            </xsl:attribute>
                    
            <xsl:attribute name="header">
                <xsl:if test="boolean(@header)">
                    <xsl:value-of select="@header"/>
                </xsl:if>
            </xsl:attribute> 
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_elib_schema"/>
                       
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <!--xsl:call-template  name="apply_visible"/-->
            
            <xsl:call-template name="apply_svg_g_visible"/> 
                                                                               
            <xsl:call-template name="apply_elib_switchertype_cursor"/>
                       
            <xsl:call-template name="apply_elib_switchertype_event"/>
            
            <xsl:call-template name="apply_elib_switchertype_style"/>
            
            <xsl:call-template name="apply_elib_switchertype_popup"/>

            <rect fill="white" stroke="white" opacity="0">
                <xsl:call-template name="apply_rect"/> 
            </rect>            
                        
            <svg viewBox="0 0 100 100" preserveAspectRatio="none"> 
            
                
                
                <xsl:call-template name="apply_rect"/>
                               
                <xsl:call-template name="apply_elib_switchertype_alarmstate"/>
             
                <xsl:call-template name="apply_elib_switchertype_state"/>
                
                <xsl:call-template name="apply_elib_switchertype_auto"/> 
                                
                <xsl:call-template name="apply_elib_switchertype_local"/>
                
                <xsl:call-template name="apply_elib_switchertype_control"/> 
                                
                <xsl:call-template name="apply_elib_switchertype_sig"/>

            </svg>
            
        </g>  
    </xsl:template>
    
    
    
    
    
    
    
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
           Компонент кнопка
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->
 
 
     <!--
    
    Установка функций управления
    
    -->
    
    
    <xsl:template name="apply_elib_button_control"> 
    
        <xsl:variable name="on_eventvar"> 
            <xsl:choose> 
                <xsl:when test="(boolean(@param) and not(normalize-space(@param)=''))">
                    <xsl:choose> 
                        <xsl:when test="(boolean(@type) and (@type='tumbler'))">
                            <xsl:text>$$('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; </xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 0) :  ((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; !</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 1) :  (0</xsl:text>                           
                            <xsl:text>)))');</xsl:text>
                        </xsl:when>
                        <xsl:when test="(boolean(@type) and (@type='button'))">
                            <xsl:text>$$('</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>');</xsl:text>                               
                        </xsl:when> 
                        <xsl:when test="(not(boolean(@type)) or (normalize-space(@type)=''))">
                            <xsl:text>$$('</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>');</xsl:text> 
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text></xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text></xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable>
        
        <xsl:variable name="mouseup_eventvar"> 
            <xsl:choose> 
                <xsl:when test="(boolean(@param) and not(normalize-space(@param)=''))">
                    <xsl:choose> 
                        <xsl:when test="(boolean(@type) and (@type='impulse'))">
                            <xsl:text>$$('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; </xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 0) : (0</xsl:text>                           
                            <xsl:text>))');</xsl:text>
                        </xsl:when>
                        <xsl:when test="(boolean(@type) and (@type='unimpulse'))">
                            <xsl:text>$$('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; !</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 1) : (0</xsl:text>                           
                            <xsl:text>))');</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text></xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text></xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
        
        <xsl:variable name="mousedown_eventvar"> 
            <xsl:choose> 
                <xsl:when test="(boolean(@param) and not(normalize-space(@param)=''))">
                    <xsl:choose> 
                        <xsl:when test="(boolean(@type) and (@type='impulse'))">
                            <xsl:text>$$('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; !</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 1) : (0</xsl:text>                           
                            <xsl:text>))');</xsl:text>
                        </xsl:when>
                        <xsl:when test="(boolean(@type) and (@type='unimpulse'))">
                            <xsl:text>$$('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; </xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 0) : (0</xsl:text>                           
                            <xsl:text>))');</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text></xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text></xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable>         

        <xsl:choose>                
            <xsl:when test="(boolean(@onclick) and not(normalize-space(@onclick)=''))">      
                <xsl:attribute name="onclick">
                    <xsl:text> if ((!this.getAttribute) || (this.getAttribute('state')!='disable')) {</xsl:text> 
                    <xsl:value-of select="@onclick"/>
                    <xsl:text>;</xsl:text> 
                    <xsl:value-of select="$on_eventvar"/>
                    <xsl:text> };</xsl:text>                       
                </xsl:attribute>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>                
                    <xsl:when test="(boolean($on_eventvar) and not($on_eventvar=''))">      
                        <xsl:attribute name="onclick">
                            <xsl:text> if ((!this.getAttribute) || (this.getAttribute('state')!='disable')) {</xsl:text> 
                            <xsl:value-of select="$on_eventvar"/>
                            <xsl:text> };</xsl:text>                       
                        </xsl:attribute>
                    </xsl:when>
                </xsl:choose>
            </xsl:otherwise>        
        </xsl:choose>
        
        <xsl:choose>                
            <xsl:when test="(boolean(@ondblclick) and not(normalize-space(@ondblclick)=''))">      
                <xsl:attribute name="ondblclick">
                    <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
                    <xsl:value-of select="@ondblclick"/>
                    <xsl:text>;</xsl:text>
                    <xsl:text> };</xsl:text>                       
                </xsl:attribute>
            </xsl:when>
        </xsl:choose>
        
        <xsl:choose>                
            <xsl:when test="(boolean(@onmouseup) and not(normalize-space(@onmouseup)=''))">      
                <xsl:attribute name="onmouseup">
                    <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
                    <xsl:value-of select="@onmouseup"/>
                    <xsl:text>;</xsl:text> 
                    <xsl:value-of select="$mouseup_eventvar"/>
                    <xsl:text> };</xsl:text>                       
                </xsl:attribute>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>                
                    <xsl:when test="(boolean($mouseup_eventvar) and not($mouseup_eventvar=''))">      
                        <xsl:attribute name="onmouseup">
                            <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
                            <xsl:value-of select="$mouseup_eventvar"/>
                            <xsl:text> };</xsl:text>                       
                        </xsl:attribute>
                    </xsl:when>
                </xsl:choose>
            </xsl:otherwise>        
        </xsl:choose>
        
        <xsl:choose>                
            <xsl:when test="(boolean(@onmousedown) and not(normalize-space(@onmousedown)=''))">      
                <xsl:attribute name="onmousedown">
                    <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
                    <xsl:value-of select="@onmousedown"/>
                    <xsl:text>;</xsl:text> 
                    <xsl:value-of select="$mousedown_eventvar"/>
                    <xsl:text> };</xsl:text>                       
                </xsl:attribute>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>                
                    <xsl:when test="(boolean($mouseup_eventvar) and not($mouseup_eventvar=''))">      
                        <xsl:attribute name="onmousedown">
                            <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
                            <xsl:value-of select="$mousedown_eventvar"/>
                            <xsl:text> };</xsl:text>                       
                        </xsl:attribute>
                    </xsl:when>
                </xsl:choose>
            </xsl:otherwise>        
        </xsl:choose>                
            
        
    </xsl:template>
    
        <!--
    
    Генерация состояния кнопки
    
    -->     
    
    <xsl:template name="apply_elib_button_state"> 
        <xsl:attribute name="state">
            <xsl:choose>                
                <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                                    
                    <xsl:choose>                   
                        <xsl:when test="(boolean(@state) and not(normalize-space(@state)=''))">   
                            <xsl:text>#{ (!(</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>) &#38;&#38; (</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>).valid) ? ( </xsl:text>
                            <xsl:text> (</xsl:text>
                            <xsl:value-of select="@state"/>
                            <xsl:text>) ? 'off' : 'on' </xsl:text>  
                            <xsl:text>): 'disable' :default disable}</xsl:text>             
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#{ (!(</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>)&#38;&#38; (</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>).valid) ? '' : 'disable' :default disable}</xsl:text>    
                        </xsl:otherwise>    
                    </xsl:choose>               
                </xsl:when>
                <xsl:otherwise>
                    <xsl:choose>                   
                        <xsl:when test="(boolean(@state) and not(normalize-space(@state)=''))">                                        
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@state"/>
                            <xsl:text>) ? 'off' : '' :default }</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>                                        
                            <xsl:text></xsl:text>                     
                        </xsl:otherwise>    
                    </xsl:choose>
                </xsl:otherwise>    
            </xsl:choose>
        </xsl:attribute> 
    </xsl:template>  
    
    
    
        <!--
    
    Генерация стиля кнопки
    
    --> 
    
    
    <xsl:template name="apply_elib_button_class">
        <xsl:choose>
            <xsl:when test="(normalize-space(@kind)='')"> 
                <xsl:attribute name="class">
                    <xsl:value-of select="@id"/>
                    <xsl:text>__elibbuttonstyle</xsl:text>
                </xsl:attribute> 
            </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_button_rectclass">
        <xsl:variable name="buttonstyle">
            <xsl:choose>
                <xsl:when test="(normalize-space(@kind)='')"> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>__elibbuttonstyle</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__elib__button_</xsl:text>
                    <xsl:value-of select="@kind"/>
                </xsl:otherwise> 
            </xsl:choose>
        </xsl:variable>
        <xsl:attribute name="class">
            <xsl:value-of select="$buttonstyle"/>
        </xsl:attribute> 
    </xsl:template>
    
     <xsl:template name="apply_elib_button_textclass">
         
      <xsl:variable name="var_fontstyle">
            <xsl:choose>
                <xsl:when test="not(normalize-space(@fontstyle)='')">
                    <xsl:value-of select="@fontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>
                 font-size: 14;
                 fill: white;
                    </xsl:text>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable>
        
        <xsl:variable name="var_offfontstyle">
            <xsl:choose>
                <xsl:when test="not(normalize-space(@offfontstyle)='')">
                    <xsl:value-of select="@offfontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$var_fontstyle"/>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable> 
        
        <xsl:variable name="var_dsblfontstyle">
            <xsl:choose>
                <xsl:when test="not(normalize-space(@dsblfontstyle)='')">
                    <xsl:value-of select="@dsblfontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>
                 font-size: 14;
                 fill: #666;
                    </xsl:text>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable>         
         
        <xsl:attribute name="class">
             <xsl:text>__elib_button_default</xsl:text>
        </xsl:attribute> 
        
        <xsl:attribute name="style">
            <xsl:choose>                
                <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                                    
                    <xsl:choose>                   
                        <xsl:when test="(boolean(@state) and not(normalize-space(@state)=''))">   
                            <xsl:text>#{ (!(</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>) &#38;&#38; (</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>).valid) ? ( </xsl:text>
                            <xsl:text> (</xsl:text>
                            <xsl:value-of select="@state"/>
                            <xsl:text>) ? '</xsl:text> 
                            <xsl:value-of select="$var_offfontstyle"/>
                            <xsl:text>' : '</xsl:text> 
                            <xsl:value-of select="$var_fontstyle"/>
                            <xsl:text>' </xsl:text>  
                            <xsl:text>): '</xsl:text> 
                            <xsl:value-of select="$var_dsblfontstyle"/>
                            <xsl:text>' :default </xsl:text> 
                            <xsl:value-of select="$var_dsblfontstyle"/>
                            <xsl:text>}</xsl:text>             
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#{ (!(</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>)&#38;&#38; (</xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>).valid) ? '</xsl:text>
                            <xsl:value-of select="$var_fontstyle"/>
                            <xsl:text>' : '</xsl:text>
                            <xsl:value-of select="$var_dsblfontstyle"/>
                            <xsl:text>' :default </xsl:text> 
                            <xsl:value-of select="$var_dsblfontstyle"/>
                            <xsl:text>}</xsl:text>    
                        </xsl:otherwise>    
                    </xsl:choose>               
                </xsl:when>
                <xsl:otherwise>
                    <xsl:choose>                   
                        <xsl:when test="not(normalize-space(@state)='')">                                        
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@state"/>
                            <xsl:text>) ? '</xsl:text>
                            <xsl:value-of select="$var_offfontstyle"/>
                            <xsl:text>' : '</xsl:text>
                            <xsl:value-of select="$var_fontstyle"/>
                            <xsl:text>' :default </xsl:text>
                            <xsl:value-of select="$var_fontstyle"/>
                            <xsl:text>}</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>                                        
                            <xsl:value-of select="$var_fontstyle"/>                    
                        </xsl:otherwise>    
                    </xsl:choose>
                </xsl:otherwise>    
            </xsl:choose>
        </xsl:attribute>         
        
        
       
    </xsl:template>
    
 
    <xsl:template name="apply_elib_button_style">       
        <xsl:choose>                
            <xsl:when test="(normalize-space(@kind)='')">        
                <xsl:variable name="buttonstyle"> 
                    <xsl:text>.</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>__elibbuttonstyle</xsl:text>
                </xsl:variable>
        
                <xsl:variable name="gradienton_id"> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>__gradienton</xsl:text>
                </xsl:variable>
                <xsl:variable name="gradientona_id"> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>__gradientona</xsl:text>
                </xsl:variable>
                <xsl:variable name="gradientoff_id"> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>__gradientoff</xsl:text>
                </xsl:variable>
                <xsl:variable name="gradientoffa_id"> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>__gradientoffa</xsl:text>
                </xsl:variable>
                <xsl:variable name="gradientdsbl_id"> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>__gradientdsbl</xsl:text>
                </xsl:variable>
                <xsl:variable name="elecselector_id"> 
                    <xsl:text>g#</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text disable-output-escaping="yes"> > svg</xsl:text>
                </xsl:variable>
        
                <xsl:variable name="var_color1">
                    <xsl:choose>
                        <xsl:when test="(boolean(@color1) and not(@color1=''))">
                            <xsl:value-of select="@color1"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#333</xsl:text>
                        </xsl:otherwise>     
                    </xsl:choose> 
                </xsl:variable>
        
                <xsl:variable name="var_color2">
                    <xsl:choose>
                        <xsl:when test="(boolean(@color2) and not(@color2=''))">
                            <xsl:value-of select="@color2"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#555</xsl:text>
                        </xsl:otherwise>     
                    </xsl:choose> 
                </xsl:variable>
        
                <xsl:variable name="var_oncolor1">
                    <xsl:choose>
                        <xsl:when test="(boolean(@oncolor1) and not(@oncolor1=''))">
                            <xsl:value-of select="@oncolor1"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#333</xsl:text>
                        </xsl:otherwise>     
                    </xsl:choose> 
                </xsl:variable>
        
                <xsl:variable name="var_oncolor2">
                    <xsl:choose>
                        <xsl:when test="(boolean(@oncolor2) and not(@oncolor2=''))">
                            <xsl:value-of select="@oncolor2"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#555</xsl:text>
                        </xsl:otherwise>     
                    </xsl:choose> 
                </xsl:variable> 
        
                <xsl:variable name="var_dsblcolor1">
                    <xsl:choose>
                        <xsl:when test="(boolean(@dsblcolor1) and not(normalize-space(@dsblcolor1)=''))">
                            <xsl:value-of select="@dsblcolor1"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#777</xsl:text>
                        </xsl:otherwise>     
                    </xsl:choose> 
                </xsl:variable>
        
                <xsl:variable name="var_dsblcolor2">
                    <xsl:choose>
                        <xsl:when test="(boolean(@dsblcolor2) and not(normalize-space(@dsblcolor2)=''))">
                            <xsl:value-of select="@dsblcolor2"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>#AAA</xsl:text>
                        </xsl:otherwise>     
                    </xsl:choose> 
                </xsl:variable>
        
        
                <style type="text/css">


                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes"> > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> {
                    </xsl:text>
                    <xsl:text>    </xsl:text>
                    <xsl:value-of select="normalize-space('fill:  url(#')"/>
                    <xsl:value-of select="$gradienton_id"/>
                    <xsl:value-of select="normalize-space(');}')"/>           
                    <xsl:text > 
            
                    </xsl:text>    
   
                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes">:active > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> {
                    </xsl:text>
                    <xsl:text>    </xsl:text>
                    <xsl:value-of select="normalize-space('fill:  url(#')"/>
                    <xsl:value-of select="$gradientona_id"/>
                    <xsl:value-of select="normalize-space(');')"/>            
                    <xsl:text disable-output-escaping="yes">  
                 
                    </xsl:text> 

    
                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes">[state="off"] > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> {
                    </xsl:text>
                    <xsl:text>    </xsl:text>
                    <xsl:value-of select="normalize-space('fill:  url(#')"/>
                    <xsl:value-of select="$gradientoff_id"/>
                    <xsl:value-of select="normalize-space(');}')"/>           
                    <xsl:text disable-output-escaping="yes"> 
                    
                    </xsl:text>    
                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes">[state="off"]:active > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> {
                    </xsl:text>
                    <xsl:text>    </xsl:text>
                    <xsl:value-of select="normalize-space('fill:  url(#')"/>
                    <xsl:value-of select="$gradientoffa_id"/>
                    <xsl:value-of select="normalize-space(');}')"/>           
                    <xsl:text disable-output-escaping="yes">           

 
           
           
                    </xsl:text>           
                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes">[state="disable"] > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> , </xsl:text>
                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes">[state="disable"]:hover > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> , </xsl:text>
                    <xsl:value-of select="$mainselector_id"/>
                    <xsl:text disable-output-escaping="yes">[state="disable"]:active > rect</xsl:text>
                    <xsl:value-of select="$buttonstyle"/>
                    <xsl:text> {
                    </xsl:text>
                    <xsl:text>     </xsl:text>               
                    <xsl:value-of select="normalize-space('fill:  url(#')"/>
                    <xsl:value-of select="$gradientdsbl_id"/>
                    <xsl:value-of select="normalize-space(');')"/>            
                    <xsl:text disable-output-escaping="yes"> } 
                
                    </xsl:text> 
                

                </style>
        
                <defs>
            
                    <xsl:call-template name="apply_lib_gradient">
                        <xsl:with-param name="id" select="$gradienton_id"/>
                        <xsl:with-param name="color1" select="$var_color1"/>
                        <xsl:with-param name="color2" select="$var_color2"/>
                    </xsl:call-template>
            
                    <xsl:call-template name="apply_lib_gradient">
                        <xsl:with-param name="id" select="$gradientona_id"/>
                        <xsl:with-param name="color1" select="$var_color2"/>
                        <xsl:with-param name="color2" select="$var_color1"/>
                    </xsl:call-template>
            
                    <xsl:call-template name="apply_lib_gradient">
                        <xsl:with-param name="id" select="$gradientoff_id"/>
                        <xsl:with-param name="color1" select="$var_oncolor1"/>
                        <xsl:with-param name="color2" select="$var_oncolor2"/>
                    </xsl:call-template>
            
                    <xsl:call-template name="apply_lib_gradient">
                        <xsl:with-param name="id" select="$gradientoffa_id"/>
                        <xsl:with-param name="color1" select="$var_oncolor2"/>
                        <xsl:with-param name="color2" select="$var_oncolor1"/>
                    </xsl:call-template>      
            
                    <xsl:call-template name="apply_lib_gradient">
                        <xsl:with-param name="id" select="$gradientdsbl_id"/>
                        <xsl:with-param name="color1" select="$var_dsblcolor1"/>
                        <xsl:with-param name="color2" select="$var_dsblcolor2"/>
                    </xsl:call-template>            
            
            
                </defs>   
                  
            </xsl:when>   
        </xsl:choose>   
    </xsl:template>  
     
    <!--
    
    Генерация тела кнопки
    
    --> 
    
    <xsl:template name="apply_elib_button_body"> 
        <svg class="__elib_button_default">
            <xsl:call-template name="apply_rect"/>
            <!--xsl:call-template name="apply_elib_button_class"/-->
            <xsl:call-template name="apply_elib_button_state"/>
            <xsl:call-template name="apply_elib_button_style"/>          
            <rect role="button" aria-pressed="true"> 
                <xsl:attribute name="x">
                    <xsl:value-of select="2"/>
                </xsl:attribute>
                <xsl:attribute name="y">
                    <xsl:value-of select="2"/>
                </xsl:attribute>
                <xsl:attribute name="height">
                    <xsl:value-of select="@height - 4"/>
                </xsl:attribute>
                <xsl:attribute name="width">
                    <xsl:value-of select="@width - 4"/>
                </xsl:attribute>
                <xsl:call-template name="apply_elib_button_rectclass"/>
                <xsl:call-template name="apply_r"/>
            </rect>   
            <xsl:call-template name="apply_elib_button_caption"/>
            <g>
                <xsl:call-template name="apply_elib_button_class"/>
                <rect class="__elib_button_default">
                    
                    <xsl:attribute name="x">
                        <xsl:value-of select="4"/>
                    </xsl:attribute>
                    <xsl:attribute name="y">
                        <xsl:value-of select="4"/>
                    </xsl:attribute>
                    <xsl:attribute name="height">
                        <xsl:value-of select="@height - 8"/>
                    </xsl:attribute>
                    <xsl:attribute name="width">
                        <xsl:value-of select="@width - 8"/>
                    </xsl:attribute>
                    <xsl:call-template name="apply_elib_button_class"/>
                    <xsl:call-template name="apply_r"/>   
                </rect>
            </g>
        </svg>
    </xsl:template>
 
 
 
    
    <!--
    
    Генерация стиля надписи
    
    -->
    
    <xsl:template name="apply_elib_button_caption_value_both">
        <xsl:text>#{ (!</xsl:text>
        <xsl:value-of select="@disable"/>
        <xsl:text> &#38;&#38;(</xsl:text>
        <xsl:value-of select="@disable"/>
        <xsl:text>).valid) ? ( </xsl:text>
        <xsl:text> (</xsl:text>
        <xsl:value-of select="@state"/>
        <xsl:text>) ? '</xsl:text>
        <xsl:value-of select="@oncaption"/> 
        <xsl:text>' : '</xsl:text>
        <xsl:value-of select="@caption"/>
        <xsl:text>' </xsl:text>  
        <xsl:text>): '</xsl:text>
        <xsl:value-of select="@dsblcaption"/>
        <xsl:text>' :default </xsl:text>
        <xsl:value-of select="@dsblcaption"/>
        <xsl:text>}</xsl:text>     
    </xsl:template> 
    
    <xsl:template name="apply_elib_button_caption_value_dsbl">
        <xsl:text>#{ (!</xsl:text>
        <xsl:value-of select="@disable"/>
        <xsl:text> &#38;&#38; (</xsl:text>
        <xsl:value-of select="@disable"/>
        <xsl:text>).valid) ? '</xsl:text>
        <xsl:value-of select="@caption"/>
        <xsl:text>' : '</xsl:text>
        <xsl:value-of select="@dsblcaption"/>
        <xsl:text>' :default </xsl:text>
        <xsl:value-of select="@dsblcaption"/>
        <xsl:text>}</xsl:text>      
    </xsl:template> 
    
    <xsl:template name="apply_elib_button_caption_value_state">
        <xsl:text>#{ (</xsl:text>
        <xsl:value-of select="@state"/>
        <xsl:text>) ? '</xsl:text>
        <xsl:value-of select="@oncaption"/>
        <xsl:text>' : '</xsl:text>
        <xsl:value-of select="@caption"/>
        <xsl:text>' :default </xsl:text>
        <xsl:value-of select="@caption"/>
        <xsl:text>}</xsl:text>   
    </xsl:template>     
    
    <xsl:template name="apply_elib_button_caption_value"> 
        <xsl:choose>
            <xsl:when test="(boolean(@oncaption) and not(normalize-space(@oncaption)=''))">
                <xsl:choose>
                    <xsl:when test="(boolean(@dsblcaption) and not(normalize-space(@dsblcaption)=''))">                       
                        <xsl:choose>
                            <xsl:when test="(boolean(@state) and not(normalize-space(@state)=''))">
                                <xsl:choose>
                                    <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                                
                                        <xsl:call-template name="apply_elib_button_caption_value_both"/>                               
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:call-template name="apply_elib_button_caption_value_state"/>                      
                                    </xsl:otherwise>     
                                </xsl:choose>                                                                                               
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:choose>
                                    <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                                
                                        <xsl:call-template name="apply_elib_button_caption_value_dsbl"/>                                
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="@caption"/>                      
                                    </xsl:otherwise>     
                                </xsl:choose>                      
                            </xsl:otherwise>     
                        </xsl:choose>                        
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:choose>
                            <xsl:when test="(boolean(@state) and not(normalize-space(@state)=''))">
                                <xsl:call-template name="apply_elib_button_caption_value_state"/>     
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:value-of select="@caption"/>                      
                            </xsl:otherwise>     
                        </xsl:choose>                                              
                    </xsl:otherwise>     
                </xsl:choose>                
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="(boolean(@dsblcaption) and not(normalize-space(@dsblcaption)=''))">                       
                        <xsl:choose>
                            <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                              
                                <xsl:call-template name="apply_elib_button_caption_value_dsbl"/>                                                                                                                                                                           
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:value-of select="@caption"/>                                                                 
                            </xsl:otherwise>     
                        </xsl:choose>
                    </xsl:when>        
                    <xsl:otherwise>
                        <xsl:value-of select="@caption"/>                                                                 
                    </xsl:otherwise>     
                </xsl:choose>
            </xsl:otherwise>  
        </xsl:choose>
    </xsl:template>
     
     
    <xsl:template name="apply_elib_button_caption"> 
        <svg> 
            <xsl:attribute name="x">
                <xsl:value-of select="4"/>
            </xsl:attribute>
            <xsl:attribute name="y">
                <xsl:value-of select="4"/>
            </xsl:attribute>
            <xsl:attribute name="height">
                <xsl:value-of select="@height - 8"/>
            </xsl:attribute>
            <xsl:attribute name="width">
                <xsl:value-of select="@width - 8"/>
            </xsl:attribute>
            <xsl:call-template name="apply_elib_button_class"/>
            <text>
                <xsl:attribute name="x">
                    <xsl:value-of select="(@width - 8) div 2"/>
                </xsl:attribute>
                <xsl:attribute name="y">
                    <xsl:value-of select="(@height - 8) div 2"/>
                </xsl:attribute>     
                <xsl:call-template name="apply_elib_button_textclass"/>
                <xsl:call-template name="apply_elib_button_caption_value"/>
                
            </text>
        </svg>     
    </xsl:template>
    
    
    
    
    <!--
    
    Основной обработчик
    
    -->
    
    
    <xsl:template match="//elib:button" name="elib_button">   
        <g>       
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>   
            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_elib_button_control"/>            
            <xsl:call-template name="apply_cental_rotate"/>             
            <xsl:call-template name="apply_svg_g_visible"/>                     
            <xsl:call-template  name="apply_elib_button_body"/>  
        </g>  
    </xsl:template>
    
    
    
   
    
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
 
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->
    
    <!-- style   -->
   
    <xsl:template name="elib_rect_style">
        
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable>
       <xsl:choose>
            <xsl:when test="normalize-space(@environment)='' and (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))">   
                <defs>
   
            
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@color1)='') and not(normalize-space(@color2)='')">
                            <xsl:call-template name="apply_lib_gradient">
                                <xsl:with-param name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_rect_gradient</xsl:text>
                                </xsl:with-param>
                                <xsl:with-param name="gradienttype" select="@gradient-type"/>
                                <xsl:with-param name="color1" select="@color1"/>
                                <xsl:with-param name="color2" select="@color2"/>
                            </xsl:call-template>                
                        </xsl:when>    
                    </xsl:choose>    
            
                    <style type="text/css">
                
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_rect_gradient_classon {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient</xsl:text>
                                <xsl:text>);}
                                </xsl:text>        
                            </xsl:when>

                            <xsl:otherwise> 
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>
                                <xsl:text>);}
                                </xsl:text> 
                            </xsl:otherwise>                    
                        </xsl:choose>
                
                        <xsl:text>
                        </xsl:text>    
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_rect_gradient_classnone {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>                
                                <xsl:text>);</xsl:text>
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:text>fill : #F7F7F7;</xsl:text>                
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:text>}
                        </xsl:text>
                
                        <xsl:text>
                        </xsl:text>    

                

                
                    </style>  
                </defs>   
            </xsl:when>
        </xsl:choose>  
        <xsl:choose>
            <xsl:when test="normalize-space(@fillenvironment)='' and (not(normalize-space(@fillcolor1)='') and not(normalize-space(@fillcolor2)=''))">   
                <defs>      
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@fillcolor1)='') and not(normalize-space(@fillcolor2)='')">
                            <xsl:call-template name="apply_lib_gradient">
                                <xsl:with-param name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_rect_gradientfill</xsl:text>
                                </xsl:with-param>
                                <xsl:with-param name="gradienttype" select="@gradient-type"/>
                                <xsl:with-param name="color1" select="@fillcolor1"/>
                                <xsl:with-param name="color2" select="@fillcolor2"/>
                            </xsl:call-template>                
                        </xsl:when>    
                    </xsl:choose>    
            
                    <style type="text/css">
                
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_rect_gradientfill_classon {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@fillcolor1)='')  and not(normalize-space(@fillcolor2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradientfill</xsl:text>
                                <xsl:text>);}
                                </xsl:text>        
                            </xsl:when>

                            <xsl:otherwise> 
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientfillnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>
                                <xsl:text>);}
                                </xsl:text> 
                            </xsl:otherwise>                    
                        </xsl:choose>
                
                        <xsl:text>
                        </xsl:text>    
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_rect_gradientfill_classnone {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@fillcolor1)='')  and not(normalize-space(@fillcolor2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientfillnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>                
                                <xsl:text>);</xsl:text>
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:text>fill : #F7F7F7;</xsl:text>                
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:text>}
                        </xsl:text>
                
                        <xsl:text>
                        </xsl:text>    
                
                    </style>  
                </defs>   
            </xsl:when>
        </xsl:choose>               
    </xsl:template>  
    
    
    
     <!-- rectclass -->  
     
    <xsl:template name="elib_rect_rectclass">       
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradnone">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_light_gray_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_light_gray_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_light_gray_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradon">
            <xsl:choose>
                <xsl:when test="normalize-space(@environment)='' and (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))">                   
                    <xsl:value-of select="@id"/>
                    <xsl:text>_rect_gradient_classon</xsl:text> 
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="elib_gradient_select">
                        <xsl:with-param name="invir" select="@environment">
                            <xsl:value-of select="@environment"/>
                        </xsl:with-param>
                        <xsl:with-param name="gradtype">
                            <xsl:value-of select="$gradtype"/>
                        </xsl:with-param>  
                    </xsl:call-template>
                </xsl:otherwise>    
            </xsl:choose>                 
        </xsl:variable> 
        
        <xsl:choose>                 
            <xsl:when test="not(normalize-space(@environment)='') or (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))"> 
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">                  
                        <xsl:attribute name="class">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="$gradon"/>
                            <xsl:text>' : '</xsl:text>                   
                            <xsl:value-of select="$gradnone"/>
                            <xsl:text>' :default </xsl:text>
                            <xsl:value-of select="$gradnone"/>
                            <xsl:text> }</xsl:text>
                        </xsl:attribute>                       
                    </xsl:when>                      
                    <xsl:otherwise>
                        <xsl:attribute name="class">
                            <xsl:value-of select="$gradon"/>
                        </xsl:attribute>    
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">                  
                        <xsl:attribute name="fill">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="@color1"/>
                            <xsl:text>' : '#333' :default #333</xsl:text>
                            <xsl:text> }</xsl:text>
                        </xsl:attribute>                       
                    </xsl:when>                      
                    <xsl:otherwise>
                        <xsl:attribute name="fill">
                            <xsl:value-of select="@color1"/>
                        </xsl:attribute>    
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:otherwise>    
        </xsl:choose>
        
    </xsl:template> 
    
     <!-- rect -->   
    
    <xsl:template name="elib_rect_rect"> 
        <rect>            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_r"/>
                
            <xsl:choose>
                <xsl:when test="boolean(@stroke-width)">
                    <xsl:attribute name="stroke-width">
                        <xsl:value-of select="@stroke-width"/>
                    </xsl:attribute>
                    <xsl:attribute name="stroke">
                        <xsl:value-of select="@stroke"/>
                    </xsl:attribute>    
                </xsl:when>
            </xsl:choose>   
                
            <xsl:call-template name="elib_rect_rectclass"/>              
        </rect>          
    </xsl:template>
    
    
   <!-- fillsrectclass -->    
    
    
    <xsl:template name="elib_fillrect_rectclass">  
    
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradnone">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_light_gray_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_light_gray_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_light_gray_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradon">
            <xsl:choose>
                <xsl:when test="normalize-space(@fillenvironment)='' and (not(normalize-space(@fillcolor1)='') or not(normalize-space(@fillcolor2)=''))">                   
                    <xsl:value-of select="@id"/>
                    <xsl:text>_rect_gradientfill_classon</xsl:text> 
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="elib_gradient_select">
                        <xsl:with-param name="invir">
                            <xsl:value-of select="@fillenvironment"/>
                        </xsl:with-param>
                        <xsl:with-param name="gradtype">
                            <xsl:value-of select="$gradtype"/>
                        </xsl:with-param>  
                    </xsl:call-template>
                </xsl:otherwise>    
            </xsl:choose>                 
        </xsl:variable> 
        
        <xsl:variable name="gradnotice">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_notice_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_notice_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_notice_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>                  
        </xsl:variable>  
        
        <xsl:variable name="gradalarm">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_alarm_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_alarm_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_alarm_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>                  
        </xsl:variable>         
 
        <xsl:variable name="gradaccident">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_accdident_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_accdident_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_accdident_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>                  
        </xsl:variable>  
        
        
        <xsl:choose>                 
            <xsl:when test="not(normalize-space(@fillenvironment)='') or (not(normalize-space(@fillcolor1)='') and not(normalize-space(@fillcolor2)=''))">  
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">            
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@alarms)='')">                    
                                <xsl:call-template name="apply_lib_alarmcheckstate_animate">
                                    <xsl:with-param name="attributeName">class</xsl:with-param>
                                    <xsl:with-param name="attributeType">XML</xsl:with-param>
                                    <xsl:with-param name="calcMode">discrete</xsl:with-param>
                                    <xsl:with-param name="alarms" select="@alarms"/>
                                    <xsl:with-param name="accident">
                                        <xsl:value-of select="$gradaccident"/>
                                    </xsl:with-param>
                                    <xsl:with-param name="alarm">
                                        <xsl:value-of select="$gradalarm"/>                     
                                    </xsl:with-param>
                                    <xsl:with-param name="notice">
                                        <xsl:value-of select="$gradnotice"/>
                                    </xsl:with-param>
                                </xsl:call-template>                                                  
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:attribute name="class">
                                    <xsl:text>#{ (</xsl:text>
                                    <xsl:value-of select="@param"/>
                                    <xsl:text>).valid  ? '</xsl:text>
                                    <xsl:value-of select="$gradon"/> 
                                    <xsl:text>' : '</xsl:text>
                                    <xsl:value-of select="$gradnone"/> 
                                    <xsl:text>' :default </xsl:text> 
                                    <xsl:value-of select="$gradnone"/> 
                                    <xsl:text>_}</xsl:text> 
                                </xsl:attribute> 
                            </xsl:otherwise>                
                        </xsl:choose>                                
                    </xsl:when>    
                </xsl:choose> 
            </xsl:when>
            <xsl:otherwise> 
               <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">            
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@alarms)='')">                    
                                <xsl:call-template name="apply_lib_alarmcheckstate_animate">
                                    <xsl:with-param name="attributeName">fill</xsl:with-param>
                                    <xsl:with-param name="attributeType">XML</xsl:with-param>
                                    <xsl:with-param name="calcMode">discrete</xsl:with-param>
                                    <xsl:with-param name="alarms" select="@alarms"/>
                                    <xsl:with-param name="accident">
                                        <xsl:text>red</xsl:text> 
                                    </xsl:with-param>
                                    <xsl:with-param name="alarm">
                                        <xsl:text>#EEAD0E</xsl:text>                   
                                    </xsl:with-param>
                                    <xsl:with-param name="notice">
                                        <xsl:text>#FF0</xsl:text>
                                    </xsl:with-param>
                                </xsl:call-template>                                                  
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:text>#{ (</xsl:text>
                                    <xsl:value-of select="@param"/>
                                    <xsl:text>).valid  ? '</xsl:text> 
                                    <xsl:value-of select="@fillcolor1"/> 
                                    <xsl:text>' : '#888' :default #888</xsl:text> 
                                    <xsl:text>}</xsl:text> 
                                </xsl:attribute> 
                            </xsl:otherwise>                
                        </xsl:choose>                                
                    </xsl:when>    
                </xsl:choose> 
            </xsl:otherwise>  
        </xsl:choose>        
        
    </xsl:template>     
    
    
   <!-- fillsrect -->
   
    

    <xsl:template name="elib_rect_fillrect">    
            
        <rect >
            
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_fill</xsl:text>
            </xsl:attribute> 
                     
            <xsl:call-template name="apply_lib_fillrectangle"> 
                <xsl:with-param name="param" select=" @param"/>
                <xsl:with-param name="x" select=" @x"/>
                <xsl:with-param name="y" select="@y"/>
                <xsl:with-param name="width" select="@width"/>
                <xsl:with-param name="height" select="@height"/>
                <xsl:with-param name="direction" select=" @direction"/>
                <xsl:with-param name="stroke-width" select="@stroke-width"/>
            </xsl:call-template>
             
            <xsl:call-template name="apply_r"/>
                
            <xsl:call-template name="elib_fillrect_rectclass"/>
               
        </rect>              
            
    </xsl:template>     
   
    
    
    <xsl:template match="//elib:erect" name="elib_rect">
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_elib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_svg_g_visible"/> 
            
            <xsl:call-template name="elib_rect_style"/>

            <xsl:call-template name="elib_rect_rect"/>            
            
            <xsl:call-template name="elib_rect_fillrect"/> 

        </g>
    </xsl:template>
    
    
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
 
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->
    
    <!-- event -->
    
    
    <xsl:template name="elib_sensor_event">
        <xsl:choose>
            <xsl:when test="not(normalize-space(@param)='')">                  
                <xsl:choose>
                    <xsl:when test="boolean(@sensorevent='valueset')"> 
                        <xsl:attribute name="onclick">
                            <xsl:text> if (eleclib.check_click(this, event)) {  </xsl:text> 
                            <xsl:text>if (event.button==0) eleclib.valueset_click(eleclib.check_click(this), '</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>',</xsl:text>
                            <xsl:value-of select="@width * 1.3"/>
                            <xsl:text>) </xsl:text> 
                             <!--xsl:call-template name="elib_config_list_check"/-->
                             <xsl:text>} </xsl:text> 
                        </xsl:attribute>    
                    </xsl:when>
                    <xsl:when test="boolean(@sensorevent='valueedit')"> 
                        <xsl:attribute name="onclick">
                            <xsl:text> if (eleclib.check_click(this, event))  {</xsl:text> 
                            <xsl:text>if (event.button==0) eleclib.valueedit_click(eleclib.check_click(this), '</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@alighn"/>                            
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@r"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@stroke"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@stroke-width"/>   
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@color1"/>
                            <xsl:text>','</xsl:text>                            
                            <xsl:value-of select="@color2"/>
                            <xsl:text>','</xsl:text>                            
                            <xsl:value-of select="@format"/>
                            <xsl:text>','</xsl:text>                            
                            <xsl:value-of select="@fontcolor"/> 
                            <xsl:text>','</xsl:text>                            
                            <xsl:value-of select="@fontstyle"/>  
                             <xsl:text>') </xsl:text>    
                             <!--xsl:call-template name="elib_config_list_check"/-->
                             <xsl:text>} </xsl:text>                              
                        </xsl:attribute>    
                    </xsl:when>                    
                    <xsl:when test="boolean(@sensorevent='graph')">
                        <xsl:attribute name="onclick">
                            <xsl:text>if (eleclib.check_click(this, event))  {</xsl:text> 
                            <xsl:text>if (event.button==0) eleclib.graph_click(eleclib.check_click(this), '</xsl:text> 
                            <xsl:value-of select="@param"/>
                            <xsl:text>','</xsl:text>  
                            <xsl:value-of select="@fontcolor"/>
                            <xsl:text>') </xsl:text>  
                             <!--xsl:call-template name="elib_config_list_check"/-->
                             <xsl:text>} </xsl:text>                               
                        </xsl:attribute> 
                    </xsl:when>     
                </xsl:choose>                    
            </xsl:when>
        </xsl:choose>         
    </xsl:template>
    
    
 <!-- style -->
    
    
    <xsl:template name="elib_sensor_style">

        <xsl:choose>
            <xsl:when test="normalize-space(@environment)='' and (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))">   
                <xsl:variable name="gradtype">
                    <xsl:choose>
                        <xsl:when test="(@gradient-type='tb')">
                            <xsl:text>v</xsl:text>
                        </xsl:when>
                        <xsl:when test="(@gradient-type='c')">
                            <xsl:text>c</xsl:text>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>h</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>    
                </xsl:variable>
                <defs>
   
            
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@color1)='') and not(normalize-space(@color2)='')">
                            <xsl:call-template name="apply_lib_gradient">
                                <xsl:with-param name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_sensor_gradient</xsl:text>
                                </xsl:with-param>
                                <xsl:with-param name="gradienttype" select="@gradient-type"/>
                                <xsl:with-param name="color1" select="@color1"/>
                                <xsl:with-param name="color2" select="@color2"/>
                            </xsl:call-template>                
                        </xsl:when>    
                    </xsl:choose>    
            
                    <style type="text/css">
                
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_sensor_gradient_classon {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_sensor_gradient</xsl:text>
                                <xsl:text>);}
                                </xsl:text>        
                            </xsl:when>

                            <xsl:otherwise> 
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>
                                <xsl:text>);}
                                </xsl:text> 
                            </xsl:otherwise>                    
                        </xsl:choose>
                
                        <xsl:text>
                        </xsl:text>    
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_sensor_gradient_classnone {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>                
                                <xsl:text>);</xsl:text>
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:text>fill : #F7F7F7;</xsl:text>                
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:text>}
                        </xsl:text>
                
                        <xsl:text>
                        </xsl:text>    

                

                
                    </style>  
                </defs>   
            </xsl:when>
        </xsl:choose>                            
    </xsl:template>      
    
    
    <!-- fill -->
    
    
    <xsl:template name="elib_sensor_fill">
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradnone">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_light_gray_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_light_gray_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_light_gray_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradon">
            <xsl:choose>
                <xsl:when test="normalize-space(@environment)='' and (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))">                   
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_gradient_classon</xsl:text> 
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="elib_gradient_select">
                        <xsl:with-param name="invir" select="@environment">
                            <xsl:value-of select="@environment"/>
                        </xsl:with-param>
                        <xsl:with-param name="gradtype">
                            <xsl:value-of select="$gradtype"/>
                        </xsl:with-param>  
                    </xsl:call-template>
                </xsl:otherwise>    
            </xsl:choose>                 
        </xsl:variable> 
        
        <xsl:choose>                 
            <xsl:when test="not(normalize-space(@environment)='') or (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))"> 
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">                  
                        <xsl:attribute name="class">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="$gradon"/>
                            <xsl:text>' : '</xsl:text>                   
                            <xsl:value-of select="$gradnone"/>
                            <xsl:text>' :default </xsl:text>
                            <xsl:value-of select="$gradnone"/>
                            <xsl:text> }</xsl:text>
                        </xsl:attribute>                       
                    </xsl:when>                      
                    <xsl:otherwise>
                        <xsl:attribute name="class">
                            <xsl:value-of select="$gradon"/>
                        </xsl:attribute>    
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">                  
                        <xsl:attribute name="fill">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="@color1"/>
                            <xsl:text>' : '#333' :default #333</xsl:text>
                            <xsl:text> }</xsl:text>
                        </xsl:attribute>                       
                    </xsl:when>                      
                    <xsl:otherwise>
                        <xsl:attribute name="fill">
                            <xsl:value-of select="@color1"/>
                        </xsl:attribute>    
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:otherwise>    
        </xsl:choose>     
    </xsl:template> 
      
    
     <!-- rect -->    
    
    <xsl:template name="elib_sensor_rect">   
        <rect>        
                
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_rect</xsl:text>
            </xsl:attribute>                   
                
            <xsl:call-template name="apply_rect"/>
                
            <xsl:choose>
                <xsl:when test="boolean(@stroke-width)">
                    <xsl:attribute name="stroke-width">
                        <xsl:value-of select="@stroke-width"/>
                    </xsl:attribute>
                    <xsl:attribute name="stroke">
                        <xsl:value-of select="@stroke"/>
                    </xsl:attribute>    
                </xsl:when>
            </xsl:choose> 
                
            <xsl:call-template name="apply_r"/>
                
            <xsl:call-template name="elib_sensor_fill"/>   
            
             <!--xsl:call-template name="elib_sensor_strokealarm"/-->
        </rect>
    </xsl:template>    
     
    <!-- cursor -->
    
    
    <xsl:template name="elib_sensor_cursor">
        <xsl:choose>
            <xsl:when test="not(normalize-space(@param)='')">                  
                <xsl:choose>
                    <xsl:when test="(@sensorevent='valueset' or @sensorevent='valueedit') and not(normalize-space(@disable)='')">                  
                        <xsl:attribute name="cursor">
                            <xsl:text>#{ </xsl:text>
                            <xsl:value-of select="@disable"/>
                            <xsl:text>  ?  'none' : 'pointer' :default none }</xsl:text>                            
                        </xsl:attribute>                       
                    </xsl:when>
                    <xsl:when test="@sensorevent='valueset' or @sensorevent='valueedit'">                  
                        <xsl:attribute name="cursor">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? 'pointer' : 'none' :default none }</xsl:text>                            
                        </xsl:attribute>                       
                    </xsl:when>                    
                    <xsl:when test="@sensorevent='graph'">                  
                        <xsl:attribute name="cursor">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? 'pointer' : 'none' :default none }</xsl:text>                            
                        </xsl:attribute>                       
                    </xsl:when>                    
                    <xsl:otherwise>
                        <xsl:attribute name="cursor">
                            <xsl:text>none</xsl:text>
                        </xsl:attribute>    
                    </xsl:otherwise> 
                </xsl:choose>                     
            </xsl:when>
            <xsl:otherwise>
                <xsl:attribute name="cursor">
                    <xsl:text>none</xsl:text>
                </xsl:attribute>    
            </xsl:otherwise> 
        </xsl:choose>         
    </xsl:template>    
    

    
    <!-- textcontent -->   
    
    <xsl:template name="elib_sensor_textcontent">     
        <xsl:choose>                              
            <xsl:when test="not(normalize-space(@param)='')">
                
                <xsl:variable name="textdefault">
                    <xsl:choose>                              
                        <xsl:when test="not(normalize-space(@caption)='')">
                            <xsl:value-of select="@caption"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>?</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:variable>
                
                <xsl:choose>                                      
                    <xsl:when test="not(normalize-space(@format)='')">
                        <xsl:text>#{ (</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>).valid ? </xsl:text>
                        <xsl:text> format(</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text> , '</xsl:text>
                        <xsl:value-of select="@format"/>
                        <xsl:text>') : '</xsl:text>
                        <xsl:value-of select="$textdefault"/>
                        <xsl:text>' :default</xsl:text> 
                        <xsl:value-of select="$textdefault"/>
                        <xsl:text>}</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>#{ (</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>).valid ? </xsl:text>
                        <xsl:text> (</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text> ) : '</xsl:text>
                        <xsl:value-of select="$textdefault"/>
                        <xsl:text>' :default</xsl:text> 
                        <xsl:value-of select="$textdefault"/>
                        <xsl:text>}</xsl:text>                                       
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>                              
                    <xsl:when test="not(normalize-space(@caption)='')">
                        <xsl:value-of select="@caption"/>
                    </xsl:when>
                </xsl:choose> 
            </xsl:otherwise>
        </xsl:choose> 
    </xsl:template>
    
    <!-- textalarm -->
    
    
    <xsl:template name="elib_sensor_textalarm">

        <xsl:choose>
            <xsl:when test="(not(normalize-space(@alarms-low)='')) or (not(normalize-space(@alarms-high)='')) or (not(normalize-space(@alarms)=''))">
                <xsl:variable name="alarm1">
                    <xsl:value-of select="@alarms-low"/> 
                </xsl:variable>
                
                <xsl:variable name="alarm2">
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@alarms-high)='')">
                            <xsl:choose>
                                <xsl:when test="not(normalize-space($alarm1)='')">                    
                                    <xsl:value-of select="$alarm1"/> 
                                    <xsl:text>,</xsl:text>
                                    <xsl:value-of select="@alarms-high"/> 
                                </xsl:when>
                                <xsl:otherwise> 
                                    <xsl:value-of select="@alarms-high"/>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:when>
                        <xsl:otherwise> 
                            <xsl:value-of select="$alarm1"/>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable> 
                
                <xsl:variable name="alarmlist">
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@alarms)='')">
                            <xsl:choose>
                                <xsl:when test="not(normalize-space($alarm2)='')">                    
                                    <xsl:value-of select="$alarm2"/> 
                                    <xsl:text>,</xsl:text>
                                    <xsl:value-of select="@alarms"/> 
                                </xsl:when>
                                <xsl:otherwise> 
                                    <xsl:value-of select="@alarms"/>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:when>
                        <xsl:otherwise> 
                            <xsl:value-of select="$alarm2"/>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable>  
                
                <xsl:call-template name="apply_lib_alarmcheckstate_animate">

                    <xsl:with-param name="attributeName">class</xsl:with-param>
                    <xsl:with-param name="attributeType">XML</xsl:with-param>
                    <xsl:with-param name="calcMode">discrete</xsl:with-param>
                    <xsl:with-param name="alarms" select="$alarmlist"/>
                    <xsl:with-param name="accident">accident</xsl:with-param>
                    <xsl:with-param name="alarm">alarm</xsl:with-param>
                    <xsl:with-param name="notice">notice</xsl:with-param>
  
                </xsl:call-template>    
                                        
            </xsl:when>                    

        </xsl:choose>        
         
    </xsl:template>       
        
    
      <!-- text --> 

    <xsl:template name="elib_sensor_text">
        <svg>
            <xsl:call-template name="apply_rect"/>
            <text>    
            
                <xsl:attribute name="id">
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_text</xsl:text>
                </xsl:attribute>            
            
                <xsl:choose>
                    <xsl:when test="boolean(@alighn) and (@alighn='left')">               
                        <xsl:attribute name="x">
                            <xsl:value-of select="@width * 0.1 "/>
                        </xsl:attribute>
                        <xsl:attribute name="y">
                            <xsl:value-of select="@height div 2"/>
                        </xsl:attribute> 
                    </xsl:when>
                    <xsl:when test="boolean(@alighn) and (@alighn='center')">               
                        <xsl:attribute name="x">
                            <xsl:value-of select="@width div 2"/>
                        </xsl:attribute>
                        <xsl:attribute name="y">
                            <xsl:value-of select="@height div 2"/>
                        </xsl:attribute> 
                    </xsl:when>
                    <xsl:otherwise>   
                        <xsl:attribute name="x">
                            <xsl:value-of select="@width * 0.9 "/>
                        </xsl:attribute>
                        <xsl:attribute name="y">
                            <xsl:value-of select="@height div 2"/>
                        </xsl:attribute> 
                    </xsl:otherwise>
                </xsl:choose>
                            
                <xsl:attribute name="style">                                       
                    <xsl:choose>
                        <xsl:when test="boolean(@alighn) and (@alighn='left')">                    
                            <xsl:text>text-anchor: start; dominant-baseline: central;  -webkit-user-select: none;</xsl:text> 
                        </xsl:when>
                        <xsl:when test="boolean(@alighn) and (@alighn='center')">                  
                            <xsl:text>text-anchor: middle; dominant-baseline: central;  -webkit-user-select: none;</xsl:text> 
                        </xsl:when>                    
                        <xsl:otherwise> 
                            <xsl:text>text-anchor: end; dominant-baseline: central;  -webkit-user-select: none;</xsl:text>    
                        </xsl:otherwise>
                    </xsl:choose> 
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@fontcolor)='') ">                   
                            <xsl:text>fill :  </xsl:text>
                            <xsl:value-of select="@fontcolor"/>                
                            <xsl:text>;</xsl:text>
                        </xsl:when>
                        <xsl:otherwise> 
                            <xsl:text>;</xsl:text>                
                        </xsl:otherwise>
                    </xsl:choose>
                    <xsl:choose>                              
                        <xsl:when test="not(@fontstyle='')">
                            <xsl:value-of select="@fontstyle"/>
                            <xsl:text>;</xsl:text>  
                        </xsl:when>    
                        <xsl:otherwise>
                            <xsl:text>fill: white; </xsl:text>
                            <xsl:text>fill-size:  </xsl:text>
                            <xsl:value-of select="@height div 1.5"/>
                            <xsl:text>;</xsl:text>                                        
                        </xsl:otherwise>
                    </xsl:choose>                                                       
                </xsl:attribute>

               
                                                   
                <xsl:call-template name="elib_sensor_textcontent"/>

                <xsl:call-template name="elib_sensor_textalarm"/>
                
                                                        
            </text>
        </svg>       
    </xsl:template> 
    
    
    <xsl:template name="apply_elib_sensor_alarmstate">    
        <xsl:choose>                
            <xsl:when test="not(normalize-space(@alarms-low)='')">
                <g  class="accident">  
                    <xsl:call-template name="apply_lib_alarm_class">
                        <xsl:with-param name="alarms" select="@alarms-low"/>
                        <xsl:with-param name="accident">accident</xsl:with-param>
                        <xsl:with-param name="alarm">alarm</xsl:with-param>
                        <xsl:with-param name="notice">notice</xsl:with-param>
                        <xsl:with-param name="default">accident</xsl:with-param>
                    </xsl:call-template>
                    
                    <polygon>
                       
                        <xsl:attribute name="points">
                            <xsl:value-of select="@x + (@width* 0.3)"/>  
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@y+ @height"/>
                            <xsl:text> </xsl:text>
                            <xsl:value-of select="@x +  (@width* 0.7)"/>   
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@y+ @height"/> 
                            <xsl:text> </xsl:text>
                            <xsl:value-of select="@x + (@width div 2)"/>  
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@y + (@height * 0.75)"/>                                                               
                        </xsl:attribute>
                        
                        <xsl:call-template name="apply_lib_alarm_animate">
                            <xsl:with-param name="attributeName">opacity</xsl:with-param>
                            <xsl:with-param name="attributeType">XML</xsl:with-param>
                            <xsl:with-param name="calcMode">linear</xsl:with-param>
                            <xsl:with-param name="alarms" select="@alarms-low"/>
                            <xsl:with-param name="on">1</xsl:with-param>
                            <xsl:with-param name="off">0</xsl:with-param> 
                        </xsl:call-template>
                        
                    </polygon>
                </g>     
            </xsl:when>   
        </xsl:choose>  
        <xsl:choose>                
            <xsl:when test="not(normalize-space(@alarms-high)='')">
                <g  class="accident"> 
                    <xsl:call-template name="apply_lib_alarm_class">
                        <xsl:with-param name="alarms" select="@alarms-high"/>
                        <xsl:with-param name="accident">accident</xsl:with-param>
                        <xsl:with-param name="alarm">alarm</xsl:with-param>
                        <xsl:with-param name="notice">notice</xsl:with-param>
                        <xsl:with-param name="default">accident</xsl:with-param>
                    </xsl:call-template>
                    
                    <polygon> 
                  
                        <xsl:attribute name="points">
                            <xsl:value-of select="@x + (@width* 0.3)"/>  
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@y "/>
                            <xsl:text> </xsl:text>
                            <xsl:value-of select="@x +  (@width* 0.7)"/>  
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@y"/> 
                            <xsl:text> </xsl:text>
                            <xsl:value-of select="@x + (@width div 2)"/>  
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@y+ (@height * 0.25)"/>                                                                                           
                        </xsl:attribute>
                    
                        <xsl:call-template name="apply_lib_alarm_animate">
                            <xsl:with-param name="attributeName">opacity</xsl:with-param>
                            <xsl:with-param name="attributeType">XML</xsl:with-param>
                            <xsl:with-param name="calcMode">linear</xsl:with-param>
                            <xsl:with-param name="alarms" select="@alarms-high"/>
                            <xsl:with-param name="on">1</xsl:with-param>
                            <xsl:with-param name="off">0</xsl:with-param> 
                        </xsl:call-template>

                    </polygon>
                </g>     
            </xsl:when>   
        </xsl:choose>         
        
    </xsl:template> 
    
    
   <!-- control --> 
    
    
    <xsl:template name="apply_elib_sensor_control_img">    
        <circle  r="3" stroke-width="0">
            <xsl:attribute name="cx">
                <xsl:value-of select="@x +  @width + 3"/> 
            </xsl:attribute> 
            <xsl:attribute name="cy">
                <xsl:value-of select="@y - 3"/>
            </xsl:attribute>         
        </circle>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_sensor_control">    
        <xsl:choose>
            <xsl:when test="not(normalize-space(@control)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@control"/>
                        <xsl:text> ? 'oncheckcontrol'  : 'offcheckcontrol' :default oncheckcontrol }</xsl:text>
                    </xsl:attribute>                              
                    <xsl:call-template name="apply_elib_sensor_control_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_sensor_calcbutton">
        <xsl:param name="id"/> 
        <xsl:param name="num"/>
        <xsl:attribute name="onclick">
            <xsl:text>var txtel= document.getElementById('</xsl:text>
            <xsl:value-of select="$id"/>
            <xsl:text>_popup_sensorcalc_sensor_text</xsl:text>  
            <xsl:text>'); if (txtel) { var newtxt= txtel.textContent+'</xsl:text>
            <xsl:value-of select="$num"/>               
            <xsl:text>'; var fltnew = parseFloat(newtxt); if (fltnew==fltnew || newtxt=='-') {txtel.textContent = newtxt;}}</xsl:text>
        </xsl:attribute>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_sensor_popup"> 
             <xsl:param name="id"/>     
                <defs>
                    <svg width="100%" height="100%" viewBox="0 0 128 250"> 
                        <xsl:attribute name="id">
                            <xsl:value-of select="$id"/>
                            <xsl:text>_popup</xsl:text>
                        </xsl:attribute>
                        
                        <xsl:variable name="fontstyle">
                            <xsl:text>fill: yellow; font-size: 18;</xsl:text>                            
                        </xsl:variable>
                           
      
                        <xsl:variable name="popupbody">
                            <sensor x="5" y="7" width="118" height="36" color1="#333"  color2="#555" caption="" r="5" fontcolor="yellow" fontstyle="font-size: 18;" stroke="#eee" stroke-width="1">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_sensorcalc</xsl:text>
                                </xsl:attribute>
                            </sensor> 
                            <button x="5" y="50" width="38" height="38" kind="custom" caption="1" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button1</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">1</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>
                            </button>    
                            <button x="45" y="50" width="38" height="38" kind="custom" caption="2" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button2</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">2</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>
                            <button x="85" y="50" width="38" height="38" kind="custom" caption="3" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button3</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">3</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>                      
                            <button x="5" y="90" width="38" height="38" kind="custom" caption="4" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button4</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">4</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>    
                            <button x="45" y="90" width="38" height="38" kind="custom" caption="5" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button5</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">5</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>
                            <button x="85" y="90" width="38" height="38" kind="custom" caption="6" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button6</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">6</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button> 
                            <button x="5" y="130" width="38" height="38" kind="custom" caption="7" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button7</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">7</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>    
                            <button x="45" y="130" width="38" height="38" kind="custom" caption="8" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button8</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">8</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>
                            <button x="85" y="130" width="38" height="38" kind="custom" caption="9" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_button9</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">9</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>                                
                            </button>    
                            <button x="5" y="170" width="38" height="38" kind="custom" caption="." r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_buttondot</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">.</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>
                            </button>    
                            <button x="45" y="170" width="38" height="38" kind="custom" caption="0" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_buttonn</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">0</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>
                            </button>
                            <button x="85" y="170" width="38" height="38" kind="custom" caption="C" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_buttonc</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="onclick">
                                    <xsl:text>var txtel= document.getElementById('</xsl:text>
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_sensorcalc_sensor_text</xsl:text>  
                                    <xsl:text>'); if (txtel) {if (txtel.textContent.length>0) {txtel.textContent=txtel.textContent.substring(0, txtel.textContent.length-1);}}</xsl:text>
                                </xsl:attribute>
                            </button>     
                            <button x="5" y="210" width="38" height="38" kind="custom" caption="-" r="5"  fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_buttonnegativ</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_elib_sensor_calcbutton">
                                    <xsl:with-param name="num">-</xsl:with-param>
                                    <xsl:with-param name="id"><xsl:value-of select="$id"/></xsl:with-param>
                                </xsl:call-template>
                            </button>    
                            <button x="45" y="210" width="38" height="38" kind="red" caption="x"  r="5" color1="#800" color2="#B00" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_buttond</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="onclick">
                                    <xsl:text>var popuptmp= document.getElementById('</xsl:text>
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_body');  if (popuptmp) {if (popuptmp.clearpopup) {popuptmp.clearpopup();}}</xsl:text>
                                </xsl:attribute>                                
                            </button>
                            <button x="85" y="210" width="38" height="38" kind="green" caption="ok"  r="5" color1="#080" color2="#0B0"  fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$id"/>
                                    <xsl:text>_popup_buttonok</xsl:text>
                                </xsl:attribute>                            
                            </button>                     
                        </xsl:variable>
                
                        <xsl:for-each select="exsl:node-set($popupbody)/*">
                            <xsl:choose>
                                <xsl:when test="local-name()='button'">
                                    <xsl:call-template name="elib_button"/>
                                </xsl:when>
                                <xsl:when test="local-name()='rect'">
                                    <xsl:call-template name="elib_button"/>
                                </xsl:when> 
                                <xsl:when test="local-name()='sensor'">
                                    <xsl:call-template name="elib_sensor"/>
                                </xsl:when>                         
                            </xsl:choose>
                        </xsl:for-each>  
                
                
                    </svg>
                </defs>  
            <!--/xsl:when>
        </xsl:choose-->
    </xsl:template>
    

        
    <xsl:template match="//elib:sensor" name="elib_sensor">
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_elib_schema"/>

            <xsl:attribute name="period">            
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@period)='')"> 
                        <xsl:value-of select="@period"/>
                    </xsl:when>  
                    <xsl:otherwise>
                        <xsl:text>600</xsl:text>
                    </xsl:otherwise>                
                </xsl:choose> 
            </xsl:attribute>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_svg_g_visible"/> 
            
            <xsl:call-template name="elib_sensor_event"/> 
            
            <xsl:call-template name="elib_sensor_cursor"/>
            
            <xsl:call-template name="elib_sensor_style"/>
            
            <xsl:call-template name="elib_sensor_rect"/> 
            
            <xsl:call-template name="elib_sensor_text"/>
            
            <xsl:call-template name="apply_elib_sensor_alarmstate"/> 
            
            <xsl:call-template name="apply_elib_sensor_control"/>
            
            <xsl:call-template name="elib_config_popup"/>
                       
        </g>
    </xsl:template>
    
    
    
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
 
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->  
    
    
    <xsl:template name="apply_elib_path_main">
        <path fill="none">
   
            <xsl:attribute name="d">
                <xsl:choose>                              
                    <xsl:when test="not(@d='')">  
                        <xsl:value-of select="@d"/>
                    </xsl:when>   
                    <xsl:otherwise> </xsl:otherwise>
                </xsl:choose>    
            </xsl:attribute>
            
            <!--xsl:choose>                              
                <xsl:when test="not(@filter='')">
                    <xsl:attribute name="filter">
                        <xsl:text>url(#filter_lib3)</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose-->
            
            <xsl:attribute name="stroke-width">
                <xsl:choose>
                    <xsl:when test="not(@stroke-width='')">  
                        <xsl:value-of select="@stroke-width"/>
                    </xsl:when>   
                    <xsl:otherwise>
                        <xsl:text>3</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:attribute> 
            
            <xsl:attribute name="class">
                <xsl:text>#{ !(</xsl:text>
                <xsl:value-of select="@on"/>
                <xsl:text>).valid  ? 'offkUNone'  : (!(</xsl:text>
                <xsl:value-of select="@on"/>
                <xsl:text>)  ? 'offkUNone</xsl:text>
                <!--xsl:value-of select="$envir"/-->
                <!--xsl:text>kUNone</xsl:text-->
                <xsl:text>':  'on</xsl:text>
                <xsl:value-of select="@environment"/>
                <xsl:text>') :default offkUNone}</xsl:text> 
            </xsl:attribute>
            
                                 
                        
            <!--xsl:attribute name="stroke">
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@on)='')"> 
                        <xsl:choose>
                            <xsl:when test="not(@stroke='')">  
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>).valid ? '</xsl:text>
                                <xsl:value-of select="@stroke"/>
                                <xsl:text>' : '#eee' :default #eee}</xsl:text>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>).valid ? '#333' : '#eee' :default #eee}</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>                     
                    </xsl:when>   
                    <xsl:otherwise>
                        <xsl:choose>
                            <xsl:when test="not(@stroke='')">  
                                <xsl:value-of select="@stroke"/>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>#333</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>  
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:attribute-->
                       
        </path>        
        
    </xsl:template>
    

    <xsl:template name="apply_elib_path_fill">
        <xsl:choose>
            <xsl:when test="not(@on='')">           
                <path fill="none">    
                    
                    <xsl:attribute name="d">
                        <xsl:choose>                              
                            <xsl:when test="not(@d='')">  
                                <xsl:value-of select="@d"/>
                            </xsl:when>   
                            <xsl:otherwise> </xsl:otherwise>
                        </xsl:choose>    
                    </xsl:attribute>
            
   
                    <xsl:attribute name="style">
                        <xsl:text>#{ </xsl:text>
                        <xsl:value-of select="@on"/>
                        <xsl:text>  ? 'display: none;' :  'display: block;' :default display: none;</xsl:text>
                        <xsl:text>}</xsl:text>
                    </xsl:attribute>

            
                    <xsl:attribute name="stroke-width">
                        <xsl:choose>
                            <xsl:when test="not(@stroke-width='')">  
                                <xsl:value-of select="@stroke-width div 1.5"/>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>1</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose> 
                    </xsl:attribute> 
                    
                    <xsl:attribute name="class">
                        <xsl:choose>
                            <xsl:when test="not(@environment='')">  
                                <xsl:text>on</xsl:text>
                                <xsl:value-of select="@environment"/>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>onevalid</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose> 
                    </xsl:attribute>               
                    
                    <!--xsl:choose>
                        <xsl:when test="(boolean(@on) and not(normalize-space(@on)='')) ">                   
                            <xsl:attribute name="visible">  
                                <xsl:text>#{ (</xsl:text>  
                                <xsl:value-of select="@on"/>
                                <xsl:text> &#38;&#38; (</xsl:text> 
                                <xsl:value-of select="@on"/>
                                <xsl:text> ).valid ) ? 'false' : 'true' :default  true;}</xsl:text> 
                            </xsl:attribute>
                        </xsl:when>   
                    </xsl:choose-->                             

            
                    <!--xsl:attribute name="stroke">
                        <xsl:choose>
                            <xsl:when test="not(@off-stroke='')">  
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>).valid ? '</xsl:text>
                                <xsl:value-of select="@off-stroke"/>
                                <xsl:text>' : '#ddd' :default #ddd}</xsl:text>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>#{ (</xsl:text>
                                <xsl:value-of select="@on"/>
                                <xsl:text>).valid ? '#000' : '#ddd' :default #ddd}</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>                     
                    </xsl:attribute-->
         
                </path>
            </xsl:when>        
        </xsl:choose>               
    </xsl:template>
    
    
    <xsl:template match="//elib:epath" >
        <g>    
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>
            <xsl:call-template name="apply_svg_g_visible"/> 

            <xsl:call-template name="apply_elib_path_main"/>
            
            <!--xsl:call-template name="apply_elib_path_fill"/-->
            
        </g> 

    </xsl:template>
    
   
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
 
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->
    
    
    <xsl:template match="//elib:alarmtable" >
         
        <foreignObject>

            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>
            
            <xsl:variable name="rectvarw"> 
                <xsl:text> width: </xsl:text> 
                <xsl:value-of select="@width"/>
                <xsl:text>px;</xsl:text>
            </xsl:variable>
         
            <xsl:variable name="rectvarh"> 
                <xsl:text> height: </xsl:text>
                <xsl:value-of select="@height"/>
                <xsl:text>px;</xsl:text>
            </xsl:variable>
            
            <xsl:variable name="rectvarfont"> 
                <xsl:choose>
                    <xsl:when test="boolean(@fontstyle) and not(@fontstyle='')">
                        <xsl:value-of select="@fontstyle"/>
                    </xsl:when>   
                    <xsl:otherwise>
                        <xsl:text>font-size: 10px;</xsl:text>
                    </xsl:otherwise>
                </xsl:choose>                       
            </xsl:variable>
             
            <html xmlns="http://www.w3.org/1999/xhtml" style=" -webkit-user-select: none;"> 
                <head xmlns="http://www.w3.org/1999/xhtml">
                    <script xmlns="http://www.w3.org/1999/xhtml"  type="text/javascript" src="../util/js/libutil.js"></script>

                    <style type="text/css">
                        body{
                          -webkit-user-select: none;
                          margin: 0px 0px; 
                          padding: 0px 0px;}

                        div{
                          float:left;
                          overflow:scroll;
                          height: 100%;
                          width: 100%;
                          border:  1px solid grey;
                          background-color: white;}

                        table{
                          border-collapse:collapse;
                          text-align: left;     
                          font-size: 13px;
                          font-family: Georgia, 'Times New Roman', Times, serif;
                          background:#f0f0f0;}

                        tbody{
                          overflow:auto;
                          margin: 0; 
                          width: 100%;}

                        tr{
                          display: table-row;
                          border-spacing: 0;
                          border: 1px solid #999999;}

                        th{
                          display: table-cell;
                          border: 1px solid #999999;
                          position: relative;
                          padding: 4px 4px;
                          text-shadow: black 1px 1px 0px, #aaa  0 0 1em;
                          color: white;
                          background:  -webkit-linear-gradient(#333 0%, #111 50%, #333 100%);}
                            
                        td{
                          display: table-cell;
                          border: 1px;                         
                          padding: 3px;
                          border: 1px solid #999999;}


                        tr.avaron{
                          color: yellow;
                          font-weight: bold;
                          background:  -webkit-linear-gradient(#600 0%, #b00 50%, #600 100%);}

                        tr.alarmon{
                          color: #220;
                          font-weight: bold;
                          background:  -webkit-linear-gradient(#f90 0%, #f60 50%, #f90 100%);}

                        tr.noticeon{
                          color: darksalmon;
                          font-weight: bold;}

                        tr.avarkvit{
                          color:  red;
                          font-weight: normal;                         
                          background:   -webkit-linear-gradient(#eee 0%, #ddd 50%, #eee 100%);}

                        tr.alarmkvit{
                          color:  #c60;
                          font-weight: normal;                         
                          background:   -webkit-linear-gradient(#eee 0%, #ddd 50%, #eee 100%);}

                        tr.noticekvit{
                          color:  lightsteelblue;
                          font-weight: normal;} 
                          
                    </style>    
                    <script type="text/javascript">                           
                        <xsl:text>document.alarmfunc___ = function(){ console.log('document.alarmfunc___'); document.alarmobj___ = new libutil.alarmtable(document.getElementById('</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>'));} </xsl:text>
                    </script>
                </head>

                <body xmlns="http://www.w3.org/1999/xhtml" onload="document.alarmfunc___()">
                    <xsl:attribute name="style">                    
                        <xsl:value-of select="$rectvarw"/>
                        <xsl:value-of select="$rectvarh"/>
                    </xsl:attribute>  
                    <div xmlns="http://www.w3.org/1999/xhtml">
                        <table> 
                            <xsl:attribute name="style">                    
                                <xsl:value-of select="$rectvarw"/>
                                <xsl:value-of select="$rectvarfont"/>
                            </xsl:attribute>  
                            <tbody xmlns="http://www.w3.org/1999/xhtml">       
                                <tr> 
                                    <xsl:attribute name="style">                    
                                        <xsl:value-of select="$rectvarw"/>
                                    </xsl:attribute>  
                                    <th width="100">Время</th>
                                    <th width="150">Имя</th>
                                    <th >Сообщение</th>
                                </tr>
                            </tbody>
                        </table>
                    </div>
                </body>
            </html>            
        </foreignObject>


    </xsl:template>
    
    
    <!--   
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    ||_______________________________________________________________________________________________________________________________________||    
 
 
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    -->   
    
    
    <xsl:template name="elib_translate"> 
        <xsl:choose>
            <xsl:when test="(not(normalize-space(@translate-x)='')) and  (not(normalize-space(@translate-y)=''))">
                <xsl:attribute name="transform">
                    <xsl:text>translate(</xsl:text>
                    <xsl:value-of select="@translate-x"/>
                    <xsl:text>,</xsl:text>
                    <xsl:value-of select="@translate-y"/>
                    <xsl:text>)</xsl:text>
                </xsl:attribute>    
                <g>
                    <xsl:call-template name="elib_rotate"/>
                </g>
            </xsl:when>
            <xsl:when test="not(normalize-space(@translate-x)='')">  
                <xsl:attribute name="transform">
                    <xsl:text>translate(</xsl:text>
                    <xsl:value-of select="@translate-x"/>
                    <xsl:text>, 0</xsl:text>
                    <xsl:text>)</xsl:text>
                </xsl:attribute>              
                <g>
                    <xsl:call-template name="elib_rotate"/>
                </g>
            </xsl:when>
            <xsl:when test="not(normalize-space(@translate-y)='')"> 
                <xsl:attribute name="transform">
                    <xsl:text>translate( 0</xsl:text>
                    <xsl:text>,</xsl:text>
                    <xsl:value-of select="@translate-y"/>
                    <xsl:text>)</xsl:text>
                </xsl:attribute>
                <g>
                    <xsl:call-template name="elib_rotate"/>
                </g>
            </xsl:when>            
            <xsl:otherwise>
                <xsl:call-template name="elib_rotate"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    

    <xsl:template name="elib_rotate"> 
        <xsl:choose>
            <xsl:when test=" (not(normalize-space(@rotate-angle)='')) or (not(normalize-space(@rotate-angle-binding)='')) ">
                <xsl:variable name="rotate-x"> 
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@rotate-x)='') ">
                            <xsl:value-of select="@rotate-x"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>0</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable>
                <xsl:variable name="rotate-y"> 
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@rotate-y)='') ">
                            <xsl:value-of select="@rotate-y"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>0</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable> 
                
                
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@rotate-angle)='') and not(normalize-space(@rotate-angle-binding)='') ">            
                        <xsl:attribute name="transform">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@rotate-angle-binding"/>
                            <xsl:text> ).valid ? </xsl:text>
                            <xsl:text>('rotate(' + format((</xsl:text>
                            <xsl:value-of select="@rotate-angle-binding"/>
                            <xsl:text>) , '%3.2f')</xsl:text>
                                                       
                            <xsl:text>+ ',</xsl:text>
                            <xsl:value-of select="$rotate-x"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-y"/>
                            <xsl:text>'</xsl:text>
                            
                            <xsl:text> + ')') : 'rotate(</xsl:text>
                            <xsl:value-of select="@rotate-angle"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-x"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-y"/>                            
                            <xsl:text>)' :default </xsl:text>
                            <xsl:text>rotate(</xsl:text>
                            <xsl:value-of select="@rotate-angle"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-x"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-y"/>
                            <xsl:text>)}</xsl:text>
                        </xsl:attribute>    
                        <g>
                            <xsl:call-template name="elib_scale"/>
                        </g>
                    </xsl:when>
                    <xsl:when test="not(normalize-space(@rotate-angle)='')">            
                        <xsl:attribute name="transform">
                            <xsl:text>rotate(</xsl:text>
                            <xsl:value-of select="@rotate-angle"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-x"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-y"/>
                            <xsl:text>)</xsl:text>
                        </xsl:attribute>    
                        <g>
                            <xsl:call-template name="elib_scale"/>
                        </g>
                    </xsl:when>
                    <xsl:when test="(not(normalize-space(@rotate-angle-binding)='')) ">            
                        <xsl:attribute name="transform">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@rotate-angle-binding"/>
                            <xsl:text> ).valid ? </xsl:text>
                            <xsl:text>('rotate(' + format((</xsl:text>
                            <xsl:value-of select="@rotate-angle-binding"/>
                            <xsl:text>) , '%3.2f')</xsl:text>
                            
                            <xsl:text>+ ',</xsl:text>
                            <xsl:value-of select="$rotate-x"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="$rotate-y"/>
                            <xsl:text>'</xsl:text>
                            
                            <xsl:text> + ')') : '</xsl:text>
                            <xsl:text>' :default }</xsl:text>
                        </xsl:attribute>    
                        <g>
                            <xsl:call-template name="elib_scale"/>
                        </g>
                    </xsl:when>            
                    <xsl:otherwise>
                        <xsl:call-template name="elib_scale"/>
                    </xsl:otherwise>
                </xsl:choose>                
             

            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="elib_scale"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template> 
    
    
    <xsl:template name="elib_scale"> 
        <xsl:choose>
            <xsl:when test="not(normalize-space(@scale)='') and not(normalize-space(@scale-binding)='') ">            
                <xsl:attribute name="transform">
                    <xsl:text>#{ (</xsl:text>
                    <xsl:value-of select="@scale-binding"/>
                    <xsl:text> ).valid ? </xsl:text>
                    <xsl:text>('scale(' + format((</xsl:text>
                    <xsl:value-of select="@scale-binding"/>
                    <xsl:text>) , '%3.2f')</xsl:text>
                    <xsl:text> + ')') : 'scale(</xsl:text>
                    <xsl:value-of select="@scale"/>
                    <xsl:text>)' :default </xsl:text>
                    <xsl:text>scale(</xsl:text>
                    <xsl:value-of select="@scale"/>
                    <xsl:text>)}</xsl:text>
                </xsl:attribute>    
                <xsl:apply-templates/>
            </xsl:when>
            <xsl:when test="not(normalize-space(@scale)='')">            
                <xsl:attribute name="transform">
                    <xsl:text>scale(</xsl:text>
                    <xsl:value-of select="@scale"/>
                    <xsl:text>)</xsl:text>
                </xsl:attribute>    
                <xsl:apply-templates/>
            </xsl:when>
            <xsl:when test="not(normalize-space(@scale-binding)='') ">            
                <xsl:attribute name="transform">
                    <xsl:text>#{ (</xsl:text>
                    <xsl:value-of select="@scale-binding"/>
                    <xsl:text> ).valid ? </xsl:text>
                    <xsl:text>('scale(' + format((</xsl:text>
                    <xsl:value-of select="@scale-binding"/>
                    <xsl:text>) , '%3.2f')</xsl:text>
                    <xsl:text> + ')') : '</xsl:text>
                    <xsl:text>' :default }</xsl:text>
                </xsl:attribute>    
                <xsl:apply-templates/>
            </xsl:when>            
            <xsl:otherwise>
                <xsl:apply-templates/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>  
    
    
    <xsl:template match="//elib:group">
        <g>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>
            <xsl:attribute name="isgoupelement">
                    <xsl:text>true</xsl:text>
            </xsl:attribute>
            <svg>
                
                <xsl:call-template name="apply_rect"/>
                <xsl:call-template name="apply_lib_mouseevent"/> 
            
                <g>
                    <xsl:call-template name="apply_svg_g_visible_binding"/>          
                    <rect stroke="white" fill="white" opacity="0.0">
                        <xsl:call-template name="apply_0_0_width_height"/> 
                    </rect>
                    <g> 
                        <xsl:call-template name="elib_translate"/>
                    </g>
                </g>
            </svg>
        </g>
    </xsl:template>    
    
    
   <!--
   
   
   slider
   
   
    -->
   
   
    <!-- style   -->
   
    <xsl:template name="apply_elib_slider_style">
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable>
        <xsl:choose>
            <xsl:when test="normalize-space(@environment)='' and (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))">   
                <defs>
   
            
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@color1)='') and not(normalize-space(@color2)='')">
                            <xsl:call-template name="apply_lib_gradient">
                                <xsl:with-param name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_slider_gradient</xsl:text>
                                </xsl:with-param>
                                <xsl:with-param name="gradienttype" select="@gradient-type"/>
                                <xsl:with-param name="color1" select="@color1"/>
                                <xsl:with-param name="color2" select="@color2"/>
                            </xsl:call-template>                
                        </xsl:when>    
                    </xsl:choose>    
            
                    <style type="text/css">
                
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient_classon {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_slider_gradient</xsl:text>
                                <xsl:text>);}
                                </xsl:text>        
                            </xsl:when>

                            <xsl:otherwise> 
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>
                                <xsl:text>);}
                                </xsl:text> 
                            </xsl:otherwise>                    
                        </xsl:choose>
                
                        <xsl:text>
                        </xsl:text>    
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient_classnone {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>                
                                <xsl:text>);</xsl:text>
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:text>fill : #F7F7F7;</xsl:text>                
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:text>}
                        </xsl:text>
                
                        <xsl:text>
                        </xsl:text>    

                

                
                    </style>  
                </defs>   
            </xsl:when>
        </xsl:choose>  
        <xsl:choose>
            <xsl:when test="normalize-space(@fillenvironment)='' and (not(normalize-space(@fillcolor1)='') and not(normalize-space(@fillcolor2)=''))">   
                <defs>
   
            
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@fillcolor1)='') and not(normalize-space(@fillcolor2)='')">
                            <xsl:call-template name="apply_lib_gradient">
                                <xsl:with-param name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_slider_gradientfill</xsl:text>
                                </xsl:with-param>
                                <xsl:with-param name="gradienttype" select="@gradient-type"/>
                                <xsl:with-param name="color1" select="@fillcolor1"/>
                                <xsl:with-param name="color2" select="@fillcolor2"/>
                            </xsl:call-template>                
                        </xsl:when>    
                    </xsl:choose>    
            
                    <style type="text/css">
                
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradientfill_classon {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@fillcolor1)='')  and not(normalize-space(@fillcolor2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_slider_gradientfill</xsl:text>
                                <xsl:text>);}
                                </xsl:text>        
                            </xsl:when>

                            <xsl:otherwise> 
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientfillnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>
                                <xsl:text>);}
                                </xsl:text> 
                            </xsl:otherwise>                    
                        </xsl:choose>
                
                        <xsl:text>
                        </xsl:text>    
                        <xsl:text>rect.</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradientfill_classnone {
                        </xsl:text>
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@fillcolor1)='')  and not(normalize-space(@fillcolor2)='')">
                                <xsl:text>fill : url(#</xsl:text>
                                <xsl:text>gradientfillnone</xsl:text>
                                <xsl:text>_</xsl:text>
                                <xsl:value-of select="$gradtype"/>                
                                <xsl:text>);</xsl:text>
                            </xsl:when>
                            <xsl:otherwise> 
                                <xsl:text>fill : #F7F7F7;</xsl:text>                
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:text>}
                        </xsl:text>
                
                        <xsl:text>
                        </xsl:text>    
                
                    </style>  
                </defs>   
            </xsl:when>
        </xsl:choose>                 
    </xsl:template>  
  
   
    <xsl:template name="apply_elib_slider_stroke">
        <xsl:attribute name="stroke">
            <xsl:choose> 
                <xsl:when test="(boolean(@stroke) and not(normalize-space(@stroke)=''))">
                    <xsl:value-of select="@stroke"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>#000</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>       
    </xsl:template>
    
    <xsl:template name="apply_elib_slider_strokewidth">
        <xsl:attribute name="stroke-width">
            <xsl:choose> 
                <xsl:when test="(boolean(@stroke-width) and not(normalize-space(@stroke-width)=''))">
                    <xsl:value-of select="@stroke-width"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>1</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>       
    </xsl:template>  
    
    
    <xsl:template name="apply_elib_slider_sliderrectclass"> 
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradnone">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_light_gray_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_light_gray_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_light_gray_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradon">
            <xsl:choose>
                <xsl:when test="normalize-space(@environment)='' and (not(normalize-space(@color1)='') or not(normalize-space(@color2)=''))">                   
                    <xsl:value-of select="@id"/>
                    <xsl:text>_slider_gradient_classon</xsl:text> 
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="elib_gradient_select">
                        <xsl:with-param name="invir" select="@environment">
                            <xsl:value-of select="@environment"/>
                        </xsl:with-param>
                        <xsl:with-param name="gradtype">
                            <xsl:value-of select="$gradtype"/>
                        </xsl:with-param>  
                    </xsl:call-template>
                </xsl:otherwise>    
            </xsl:choose>                 
        </xsl:variable> 
        
        <xsl:choose>                 
            <xsl:when test="not(normalize-space(@environment)='') or (not(normalize-space(@color1)='') and not(normalize-space(@color2)=''))"> 
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">                  
                        <xsl:attribute name="class">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="$gradon"/>
                            <xsl:text>' : '</xsl:text>                   
                            <xsl:value-of select="$gradnone"/>
                            <xsl:text>' :default </xsl:text>
                            <xsl:value-of select="$gradnone"/>
                            <xsl:text> }</xsl:text>
                        </xsl:attribute>                       
                    </xsl:when>                      
                    <xsl:otherwise>
                        <xsl:attribute name="class">
                            <xsl:value-of select="$gradon"/>
                        </xsl:attribute>    
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">                  
                        <xsl:attribute name="fill">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="@color1"/>
                            <xsl:text>' : '#333' :default #333</xsl:text>
                            <xsl:text> }</xsl:text>
                        </xsl:attribute>                       
                    </xsl:when>                      
                    <xsl:otherwise>
                        <xsl:attribute name="fill">
                            <xsl:value-of select="@color1"/>
                        </xsl:attribute>    
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:otherwise>    
        </xsl:choose> 
        
    </xsl:template>      
    
    
    <xsl:template name="apply_elib_slider_sliderrect"> 
        <rect>
            
            <xsl:variable name="kh">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">0.9</xsl:when>
                    <xsl:otherwise>0.36</xsl:otherwise>
                </xsl:choose>
            </xsl:variable>
            
            <xsl:variable name="kw">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">0.36</xsl:when>
                    <xsl:otherwise>0.9</xsl:otherwise>
                </xsl:choose>
            </xsl:variable>     
           
            <xsl:call-template name="apply_parametred_rect">          
                <xsl:with-param name="x" select=" @width * (1 - $kw) div 2"/>
                <xsl:with-param name="y" select="@height  * (1 - $kh) div 2"/>
                <xsl:with-param name="width" select="@width *  $kw "/>
                <xsl:with-param name="height" select="@height * $kh"/>
            </xsl:call-template>  
        
            <xsl:call-template name="apply_r"/>
            
            <xsl:call-template name="apply_elib_slider_sliderrectclass"/>
            
            <xsl:call-template name="apply_elib_slider_stroke"/>
            <xsl:call-template name="apply_elib_slider_strokewidth"/>
    
        </rect>
    </xsl:template>
    
    
    <xsl:template name="apply_elib_slider_sliderfillrectclass"> 
        <xsl:variable name="gradtype">
            <xsl:choose>
                <xsl:when test="(@gradient-type='tb')">
                    <xsl:text>v</xsl:text>
                </xsl:when>
                <xsl:when test="(@gradient-type='c')">
                    <xsl:text>c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradnone">
            <xsl:choose>
                <xsl:when test="($gradtype='tb')">
                    <xsl:text>__fill_elib_class_light_gray_v</xsl:text>
                </xsl:when>
                <xsl:when test="($gradtype='c')">
                    <xsl:text>__fill_elib_class_light_gray_c</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>__fill_elib_class_light_gray_h</xsl:text>
                </xsl:otherwise>
            </xsl:choose>    
        </xsl:variable> 
            
        <xsl:variable name="gradon">
            <xsl:choose>
                <xsl:when test="normalize-space(@fillenvironment)='' and (not(normalize-space(@fillcolor1)='') or not(normalize-space(@fillcolor2)=''))">                   
                    <xsl:value-of select="@id"/>
                    <xsl:text>_slider_gradientfill_classon</xsl:text> 
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="elib_gradient_select">
                        <xsl:with-param name="invir">
                            <xsl:value-of select="@fillenvironment"/>
                        </xsl:with-param>
                        <xsl:with-param name="gradtype">
                            <xsl:value-of select="$gradtype"/>
                        </xsl:with-param>  
                    </xsl:call-template>
                </xsl:otherwise>    
            </xsl:choose>                 
        </xsl:variable> 
        
        <xsl:choose>                 
            <xsl:when test="not(normalize-space(@fillenvironment)='') or (not(normalize-space(@fillcolor1)='') and not(normalize-space(@fillcolor2)=''))">  
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">             
                        <xsl:attribute name="class">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text>
                            <xsl:value-of select="$gradon"/> 
                            <xsl:text>' : '</xsl:text>
                            <xsl:value-of select="$gradnone"/> 
                            <xsl:text>' :default </xsl:text> 
                            <xsl:value-of select="$gradnone"/> 
                            <xsl:text>_}</xsl:text> 
                        </xsl:attribute>                             
                    </xsl:when>    
                </xsl:choose> 
            </xsl:when>
            <xsl:otherwise> 
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@param)='')">            
                        <xsl:attribute name="fill">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '</xsl:text> 
                            <xsl:value-of select="@fillcolor1"/> 
                            <xsl:text>' : '#888' :default #888</xsl:text> 
                            <xsl:text>}</xsl:text> 
                        </xsl:attribute>                       
                    </xsl:when>    
                </xsl:choose> 
            </xsl:otherwise>  
        </xsl:choose> 
        
    </xsl:template>     
    
    <xsl:template name="apply_elib_slider_sliderfillrect"> 
        <rect stroke="none">
            
            <xsl:attribute name="id">            
                <xsl:value-of select="@id"/>
                <xsl:text>_slider_fill</xsl:text>  
            </xsl:attribute>  
        
            <xsl:variable name="kh">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">0.9</xsl:when>
                    <xsl:otherwise>0.36</xsl:otherwise>
                </xsl:choose>
            </xsl:variable>
            
            <xsl:variable name="kw">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">0.36</xsl:when>
                    <xsl:otherwise>0.9</xsl:otherwise>
                </xsl:choose>
            </xsl:variable>
            
            <xsl:call-template name="apply_elib_slider_sliderfillrectclass"/>
            
            <xsl:call-template name="apply_lib_fillrectangle"> 
                <xsl:with-param name="param" select=" @param"/>
                <xsl:with-param name="x" select=" @width * (1 - $kw) div 2"/>
                <xsl:with-param name="y" select="@height  * (1 - $kh) div 2"/>
                <xsl:with-param name="width" select="@width *  $kw"/>
                <xsl:with-param name="height" select="@height * $kh"/>
                <xsl:with-param name="direction" select=" @direction"/>
                <xsl:with-param name="stroke-width" select="@stroke-width"/>
            </xsl:call-template>
                       
            <xsl:call-template name="apply_elib_slider_strokewidth"/>
            
            <xsl:call-template name="apply_r"/>
    
        </rect>
    </xsl:template> 
    

   
    
    <xsl:template name="apply_elib_slider_button"> 
        <xsl:param name="size"/>
        <defs>
            <symbol>
                <xsl:attribute name="id">            
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sliderbuttondef</xsl:text>  
                </xsl:attribute>
                <circle cx="{$size div 2}" cy="{$size div 2}" r="{$size}" stroke="0" stroke-width="0" fill="black" opacity="0">
                </circle> 
                <circle cx="{$size div 2}" cy="{$size div 2}" r="{$size div 2}" stroke="{@stroke}" stroke-width="{@stroke-width}">
                    <xsl:attribute name="fill">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@slidercolor1)='')">
                                <xsl:value-of select="@slidercolor1"/>
                            </xsl:when>
                            <xsl:otherwise>green</xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>
                </circle> 
                <circle cx="{$size div 2}" cy="{$size div 2}" r="{$size div 3}" stroke="{@stroke}" stroke-width="0">
                    <xsl:attribute name="fill">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@slidercolor2)='')">
                                <xsl:value-of select="@slidercolor2"/>
                            </xsl:when>
                            <xsl:otherwise>red</xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>
                </circle>                 
            </symbol>
        </defs>    
    </xsl:template>    
    
    
    <xsl:template name="apply_elib_slider_buttoncontrol"> 
    
        <xsl:variable name="kh">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">0.9</xsl:when>
                <xsl:otherwise>0.36</xsl:otherwise>
            </xsl:choose>
        </xsl:variable>
            
        <xsl:variable name="kw">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">0.36</xsl:when>
                <xsl:otherwise>0.9</xsl:otherwise>
            </xsl:choose>
        </xsl:variable> 
        
        <xsl:variable name="x1">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                    <xsl:value-of select="@width * 0.5"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@width * (1 - $kw) div 2"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable> 
        
        <xsl:variable name="y1">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                    <xsl:value-of select="@height * (1 - $kh) div 2"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@height * 0.5"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable> 
        
        <xsl:variable name="x2">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                    <xsl:value-of select="@width * 0.5"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@width *((1 - $kw) div 2 + $kw)"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable>
        
        <xsl:variable name="y2">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                    <xsl:value-of select="@height *((1 - $kh) div 2 + $kh)"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@height * 0.5"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable>
 
        <xsl:variable name="rev">
            <xsl:choose>
                <xsl:when test="boolean(@direction='bt') or boolean(@direction='rl')">r</xsl:when>
                <xsl:otherwise></xsl:otherwise>
            </xsl:choose>
        </xsl:variable>
        
        <xsl:variable name="buttonsize">
            <xsl:choose>
                <xsl:when test="@width &lt; @height">
                    <xsl:value-of select="@width * 0.5"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="@height * 1"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable>
                    
        <!--line x1="{$x1}" x2="{$x2}" y1="{$y1}" y2="{$y2}" stroke="#003" stroke-width="3" direct="{$rev}"/-->
        
        <xsl:call-template name="apply_elib_slider_button">
            <xsl:with-param name="size" select="$buttonsize"/>
        </xsl:call-template>            
            
        
    
        <use>
            
            <xsl:attribute name="id">            
                <xsl:value-of select="@id"/>
                <xsl:text>_sliderbutton</xsl:text>  
            </xsl:attribute>
            
            <xsl:attribute name="transform"> 
                <xsl:text>translate( -</xsl:text>
                <xsl:value-of select="$buttonsize div 2"/>
                <xsl:text>, -</xsl:text> 
                <xsl:value-of select="$buttonsize div 2"/>
                <xsl:text>)</xsl:text>  
            </xsl:attribute>
            
            <xsl:attribute name="xlink:href"> 
                <xsl:text>#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sliderbuttondef</xsl:text>  
            </xsl:attribute> 
            
            <xsl:attribute name="width">            
                <xsl:value-of select="$buttonsize"/> 
            </xsl:attribute>
            
            <xsl:attribute name="height">            
                <xsl:value-of select="$buttonsize"/>   
            </xsl:attribute>            
            
             
            <xsl:attribute  name="y">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@param)='')">
                                <xsl:text>#{ </xsl:text>
                                <xsl:text>(</xsl:text>
                                <xsl:if test="boolean($rev='r')">
                                    <xsl:text> 1 - </xsl:text>
                                </xsl:if>
                                <xsl:text>(&#38;</xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text> - </xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text>.mineu)/(</xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text>.maxeu-</xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text>.mineu)) * </xsl:text>
                                <xsl:value-of select="$y2 - $y1"/>
                                <xsl:text> + </xsl:text>
                                <xsl:value-of select="$y1"/>
                                <xsl:text> :default </xsl:text>
                                <xsl:choose>
                                    <xsl:when test="boolean($rev='r')">
                                        <xsl:value-of select="$y2"/>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="$y1"/>
                                    </xsl:otherwise>
                                </xsl:choose>
                                <xsl:text> }</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:choose>
                                    <xsl:when test="boolean($rev='r')">
                                        <xsl:value-of select="$y2"/>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="$y1"/>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:when>
                    <xsl:otherwise>                       
                        <xsl:value-of select="$y1"/>                                            
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:attribute>
            
            <xsl:attribute name="x">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                        <xsl:value-of select="$x1"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:choose>
                            <xsl:when test="(boolean(@param) and not(normalize-space(@param)=''))">
                                <xsl:text>#{ </xsl:text>
                                <xsl:text>(</xsl:text>
                                <xsl:if test="boolean($rev='r')">
                                    <xsl:text> 1 - </xsl:text>
                                </xsl:if>
                                <xsl:text>(&#38;</xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text> - </xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text>.mineu)/(</xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text>.maxeu-</xsl:text>
                                <xsl:value-of select="@param"/>
                                <xsl:text>.mineu)) * </xsl:text>
                                <xsl:value-of select="$x2 - $x1"/>
                                <xsl:text> + </xsl:text>
                                <xsl:value-of select="$x1"/>
                                <xsl:text> :default </xsl:text>
                                <xsl:choose>
                                    <xsl:when test="boolean($rev='r')">
                                        <xsl:value-of select="$x2"/>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="$x1"/>
                                    </xsl:otherwise>
                                </xsl:choose>
                                <xsl:text> }</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:choose>
                                    <xsl:when test="boolean($rev='r')">
                                        <xsl:value-of select="$x2"/>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="$x1"/>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </xsl:otherwise> 
                        </xsl:choose>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:attribute>  
            
            <xsl:attribute name="r">
                <xsl:value-of select="$buttonsize div 2"/>      
            </xsl:attribute>
            
          
            <xsl:attribute name="onmousedown">   
                <xsl:text> this.tmpslidertarget = eleclib.check_click(this); if (this.tmpslidertarget) {this.tmpslidertarget.setAttribute('class','captured');eleclib.create_shadow_slider(this.tmpslidertarget,</xsl:text>
                <xsl:value-of select="$x1"/>
                <xsl:text> ,  </xsl:text> 
                <xsl:value-of select="$y1"/>
                <xsl:text> ,  </xsl:text>
                <xsl:value-of select="$x2"/>
                <xsl:text> ,  </xsl:text> 
                <xsl:value-of select="$y2"/>
                <xsl:text>, '</xsl:text>
                <xsl:value-of select="@direction"/>
                <xsl:text>' </xsl:text>                
                <xsl:text>, '</xsl:text>
                <xsl:value-of select="@param"/>
                <xsl:text>' , </xsl:text>
                <xsl:choose> 
                    <xsl:when test="(boolean(@live-command) and (normalize-space(@live-command)='live'))"> 
                        <xsl:text>true</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>false</xsl:text>
                    </xsl:otherwise>     
                </xsl:choose> 
                
                <xsl:choose> 
                    <xsl:when test="(boolean(@wait-timeout) and not(normalize-space(@wait-timeout)=''))"> 
                        <xsl:text> , </xsl:text>
                        <xsl:value-of select="@wait-timeout"/>
                    </xsl:when>   
                </xsl:choose> 
                <xsl:text>);}</xsl:text>             
            </xsl:attribute>  
            
            
            <xsl:attribute name="onmouseup">   
                <xsl:text>this.tmpslidertarget = eleclib.check_click(this); if (this.tmpslidertarget.hasAttribute('class'))  {  console.log('removeslidershadow');  this.tmpslidertarget.setAttribute('class',''); }</xsl:text>            
            </xsl:attribute> 
            
            <xsl:call-template name="elib_slider_cursor"/>
            
            <xsl:call-template name="apply_elib_slider_stroke"/>
            
            <xsl:call-template name="apply_elib_slider_strokewidth"/> 
            
        </use>    
    </xsl:template>  
    
    <xsl:template name="elib_slider_cursor">
        <xsl:choose>
            <xsl:when test="not(normalize-space(@param)='') and not(normalize-space(@disable)='')">                                
                <xsl:attribute name="cursor">
                    <xsl:text>#{ </xsl:text>
                    <xsl:value-of select="@disable"/>
                    <xsl:text>  ?  'none' : 'pointer' :default none }</xsl:text>                       
                </xsl:attribute>                       
            </xsl:when>
            <xsl:when test="not(normalize-space(@param)='')">                                
                <xsl:attribute name="cursor">
                    <xsl:text>#{ (</xsl:text>
                    <xsl:value-of select="@param"/>
                    <xsl:text>).valid  ? 'pointer' : 'none' :default none }</xsl:text>                            
                </xsl:attribute>                       
            </xsl:when>            
            <xsl:otherwise>
                <xsl:attribute name="cursor">
                    <xsl:text>none</xsl:text>
                </xsl:attribute>    
            </xsl:otherwise> 
        </xsl:choose>         
    </xsl:template> 
   
   
    <xsl:template match="//elib:slider" name="elib_slider">
        <g>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>            
            <svg>        
                <xsl:call-template name="apply_rect"/>
                <xsl:call-template name="apply_svg_g_visible_binding"/>           
                <xsl:call-template name="apply_elib_slider_style"/>
                <g>           
                    <rect stroke="white" fill="white" opacity="0.0">
                        <xsl:call-template name="apply_0_0_width_height"/> 
                    </rect>
                
                    <xsl:call-template name="apply_elib_slider_sliderrect"/>
                
                    <xsl:call-template name="apply_elib_slider_sliderfillrect"/>
                
                    <xsl:call-template name="apply_elib_slider_buttoncontrol"/> 
                </g>
            </svg>
        </g>
    </xsl:template>   
    
    
    
    <!--    Компонент отображающий  график
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    --> 
    
    <xsl:template match="//elib:chart"  name="elib_chart">
        <g>  
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>
            <svg>        
                <xsl:attribute name="id">
                    <xsl:value-of select="@id"/>
                    <xsl:text>_chartbackground</xsl:text>                 
                </xsl:attribute>            
                <xsl:call-template name="apply_rect"/>          
                <rect>                 
                    <xsl:call-template name="apply_0_0_width_height"/>
                    <xsl:call-template name="apply_r"/>
                    <xsl:attribute name="style">
                        <xsl:choose>                      
                            <xsl:when test="not(normalize-space(@layer-style)='')">                            
                                <xsl:value-of select="@layer-style"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>fill: #777; opacity: 0.5; stroke: #333; stroke-width: 1;</xsl:text>
                            </xsl:otherwise>                                                         
                        </xsl:choose> 
                    </xsl:attribute>                    
                </rect>   
            </svg>    
            <svg>
                <xsl:call-template name="apply_rect"/>
                <foreignObject>
                    <xsl:attribute name="height">
                        <xsl:value-of select="@height"/>
                    </xsl:attribute>
                    <xsl:attribute name="width">
                        <xsl:value-of select="@width"/>
                    </xsl:attribute>
                    <html xmlns="http://www.w3.org/1999/xhtml">
                        <head xmlns="http://www.w3.org/1999/xhtml">
                                          
                        </head>    
                        <body xmlns="http://www.w3.org/1999/xhtml" style="padding: 0px 0px; margin: 0px 0px;">
                            <div xmlns="http://www.w3.org/1999/xhtml" style="padding: 0px 0px; margin: 0px 0px;">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_chartbody</xsl:text>                            
                                </xsl:attribute>                             
                            </div>
                            <xsl:choose>                      
                                <xsl:when test="not(normalize-space(@params)='')">                         
                                    <script xmlns="http://www.w3.org/1999/xhtml"  type="text/javascript">
                                        <xsl:text>try { new libutil.trendchart( {element: '</xsl:text>
                                        <xsl:value-of select="@id"/>
                                        <xsl:text>_chartbody' , throbler: '</xsl:text>
                                        <xsl:value-of select="@id"/>
                                        <xsl:text>_chartbackground' ,  tags:  </xsl:text>
                                        <xsl:value-of select="@params"/>
                                        <xsl:text> , hist: </xsl:text>
                                        <xsl:choose>                      
                                            <xsl:when test="not(normalize-space(@period)='')"> 
                                                <xsl:value-of select="@period"/>
                                            </xsl:when>  
                                            <xsl:otherwise>
                                                <xsl:text>600</xsl:text>
                                            </xsl:otherwise>   
                                        </xsl:choose> 
                                        <xsl:text> , colors: </xsl:text>
                                        <xsl:choose>                      
                                            <xsl:when test="not(normalize-space(@colors)='')"> 
                                                <xsl:value-of select="@colors"/>
                                            </xsl:when>  
                                            <xsl:otherwise>
                                                <xsl:text>null</xsl:text>
                                            </xsl:otherwise>   
                                        </xsl:choose>                                   
                                        <xsl:text> , width: </xsl:text>
                                        <xsl:value-of select="@width"/>
                                        <xsl:text> , height: </xsl:text>
                                        <xsl:value-of select="@height"/> 
                                        <xsl:text> , r: </xsl:text>
                                        <xsl:choose>                      
                                            <xsl:when test="not(normalize-space(@r)='')"> 
                                                <xsl:value-of select="@r"/>
                                            </xsl:when>  
                                            <xsl:otherwise>
                                                <xsl:text>5</xsl:text>
                                            </xsl:otherwise>   
                                        </xsl:choose> 
                                        <xsl:text> ,  </xsl:text>
                                        <xsl:choose>                      
                                            <xsl:when test="not(normalize-space(@option)='')"> 
                                                <xsl:value-of select="@option"/>
                                            </xsl:when>  
                                            <xsl:otherwise>
                                                <xsl:text></xsl:text>
                                            </xsl:otherwise>   
                                        </xsl:choose>                                    
                                        <xsl:text> } ); }  catch(error){</xsl:text> 
                                        
                                        <xsl:text> }</xsl:text> 
                                    </script>
                                </xsl:when>          
                            </xsl:choose>    
                        </body>
                    </html>
                </foreignObject>
            </svg>
            <rect style="fill: white; opacity: 0; stoke: none; stroke-width: 0; display: none;" class="design_captured">              
                <xsl:call-template name="apply_rect"/>
                <xsl:call-template name="apply_r"/>                
            </rect>             
        </g>        
    </xsl:template>         
    
    <!--    Компонент отображающий  регулятор
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||
    ||_______________________________________________________________________________________________________________________________________||    
    --> 
    
    
     
    
    <xsl:template name="elib_regulator_control">
        <xsl:param name="shift"/>
        <xsl:param name="preff"/>
        <xsl:param name="param"/>
        <xsl:param name="param-sp"/>
        <xsl:param name="header"/>
        <xsl:param name="headerparam"/>
        <xsl:param name="headerparam-sp"/>    
        <xsl:param name="format"/>
        <xsl:param name="disable"/>  
        <xsl:param name="color"/> 
        <xsl:param name="color2"/> 
        <xsl:param name="еnvironment"/>
        <xsl:param name="fillеnvironment"/>

        <svgrect x="5" height="110" width="240" fill="#333" stroke="#ccc" stroke-width="1" r="4">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_headset_</xsl:text>
                <xsl:value-of select="$preff"/>  
            </xsl:attribute> 
            <xsl:attribute name="y">
                <xsl:value-of select="$shift"/>                            
            </xsl:attribute> 
        </svgrect>                       
        <elib:sensor x="10"  height="18" width="60" stroke="#eee" stroke-width="0.5" r="2"   fontstyle="font-size: 12" color1="#001">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_</xsl:text>
                <xsl:value-of select="$preff"/>
            </xsl:attribute>  
            <xsl:attribute name="param">
                <xsl:value-of select="$param"/>                            
            </xsl:attribute> 
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 32"/>                            
            </xsl:attribute>
            <xsl:attribute name="fontcolor">
                <xsl:value-of select="$color"/>                            
            </xsl:attribute>               
            <xsl:attribute name="format">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($format)='')">  
                        <xsl:value-of select="$format"/> 
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:text>%3.0f</xsl:text>
                    </xsl:otherwise>                      
                </xsl:choose>                       
            </xsl:attribute>             
        </elib:sensor>                    
        <elib:sensor x="135"  height="18" width="60" stroke="#eee" stroke-width="0.5" r="2" color1="#001"  fontstyle="font-size: 12" sensorevent="valueset" >
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_</xsl:text>
                <xsl:value-of select="$preff"/>
                <xsl:text>_sp</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="param">
                <xsl:value-of select="$param-sp"/>                            
            </xsl:attribute> 
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 32"/>                            
            </xsl:attribute>
            <xsl:attribute name="fontcolor">
                <xsl:value-of select="$color"/>                            
            </xsl:attribute>
            <xsl:attribute name="format">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($format)='')">  
                        <xsl:value-of select="$format"/> 
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:text>%3.0f</xsl:text>
                    </xsl:otherwise>                      
                </xsl:choose>                       
            </xsl:attribute>  
            <xsl:attribute name="disable">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($disable)='')">  
                        <xsl:value-of select="$disable"/> 
                    </xsl:when> 
                </xsl:choose>
            </xsl:attribute>                
        </elib:sensor>   
        <elib:button x="200"  height="15" width="15" caption="+"  kind="custom" alighn="center"  dsblfontstyle="font-size: 4; fill: #333;" disable="level_sp &gt;= level_sp.maxeu">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_buttoninc_</xsl:text>
                <xsl:value-of select="$preff"/>
                <xsl:text>_sp</xsl:text>
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 28"/>                            
            </xsl:attribute>
            <xsl:attribute name="fontstyle">
                <xsl:text>font-size: 4; fill: </xsl:text> 
                <xsl:value-of select="$color"/>
                <xsl:text>;</xsl:text>
            </xsl:attribute> 
            <xsl:attribute name="onclick">
                <xsl:text>$$('((</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text> &lt;</xsl:text> 
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.maxeu) &amp;&amp; (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.valid)) ? (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>@ (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>+ (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.maxeu-</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.mineu) / 100)) : 0')</xsl:text> 
                <xsl:text>;</xsl:text>
            </xsl:attribute>
            <xsl:attribute name="disable">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($disable)='')">
                        <xsl:value-of select="$param-sp"/> 
                        <xsl:text>&gt;=</xsl:text>
                        <xsl:value-of select="$param-sp"/>
                        <xsl:text>.maxeu ||</xsl:text>
                        <xsl:value-of select="$disable"/> 
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:value-of select="$param-sp"/> 
                        <xsl:text>&gt;=</xsl:text>
                        <xsl:value-of select="$param-sp"/>
                        <xsl:text>.maxeu</xsl:text>
                    </xsl:otherwise> 
                </xsl:choose>                
            </xsl:attribute> 
        </elib:button>
        <elib:button x="200" height="15" width="15" caption="-" kind="custom" alighn="center"  dsblfontstyle="font-size: 4; fill: #333;">        
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_buttondec_</xsl:text>
                <xsl:value-of select="$preff"/>
                <xsl:text>_sp</xsl:text>
            </xsl:attribute> 
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 40"/>                            
            </xsl:attribute> 
            <xsl:attribute name="fontstyle">
                <xsl:text>font-size: 4; fill: </xsl:text> 
                <xsl:value-of select="$color"/>
                <xsl:text>;</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="onclick">
                <xsl:text>$$('((</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text> &gt;</xsl:text> 
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.mineu) &amp;&amp; (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.valid)) ? (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>@ (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>- (</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.maxeu-</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.mineu) / 100)) : 0')</xsl:text> 
                <xsl:text>;</xsl:text>
            </xsl:attribute> 
            <xsl:attribute name="disable">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($disable)='')">
                        <xsl:value-of select="$param-sp"/> 
                        <xsl:text>&lt;=</xsl:text>
                        <xsl:value-of select="$param-sp"/>
                        <xsl:text>.mineu ||</xsl:text>
                        <xsl:value-of select="$disable"/> 
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:value-of select="$param-sp"/> 
                        <xsl:text>&lt;=</xsl:text>
                        <xsl:value-of select="$param-sp"/>
                        <xsl:text>.mineu</xsl:text>
                    </xsl:otherwise> 
                </xsl:choose>                
            </xsl:attribute>             
        </elib:button>
        <line stroke="#eee" stroke-width="4" x1="0" y1="0" x2="221" y2="0" stroke-dasharray="1 109">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_scalehigh_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_name</xsl:text>
            </xsl:attribute>   
            <xsl:attribute name="transform">
                <xsl:text>translate(15 ,</xsl:text> 
                <xsl:value-of select="$shift + 94"/> 
                <xsl:text>)</xsl:text>
            </xsl:attribute>               
        </line> 
        <line stroke="#eee" stroke-width="2"  x1="0" y1="0" x2="221" y2="0" stroke-dasharray="1 21">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_scalelow_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_name</xsl:text>
            </xsl:attribute>   
            <xsl:attribute name="transform">
                <xsl:text>translate(15 ,</xsl:text> 
                <xsl:value-of select="$shift + 94"/> 
                <xsl:text>)</xsl:text>
            </xsl:attribute>               
        </line>  
        <text x="8" fill="#eee"  style="text-anchor: start; font-size: 8;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_textleftval_</xsl:text>  
                <xsl:value-of select="$preff"/>
                <xsl:text>_pos</xsl:text> 
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 105"/>                            
            </xsl:attribute>    
            <xsl:attribute name="text">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($param)='')">  
                        <xsl:text>#{ format(</xsl:text>
                        <xsl:value-of select="$param"/>
                        <xsl:text>.mineu , '</xsl:text> 
                        <xsl:choose>
                            <xsl:when test="not(normalize-space($format)='')">
                                <xsl:value-of select="$format"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>%3.0f</xsl:text>
                            </xsl:otherwise> 
                        </xsl:choose>                                    
                        <xsl:text>') :default 0}</xsl:text> 
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:text>0</xsl:text>
                    </xsl:otherwise> 
                </xsl:choose>  
            </xsl:attribute>              
        </text> 
        <text x="240" fill="#eee"  style="text-anchor: end; font-size: 8;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_textrightval_</xsl:text>  
                <xsl:value-of select="$preff"/>
                <xsl:text>_pos</xsl:text> 
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 105"/>                            
            </xsl:attribute>    
            <xsl:attribute name="text">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($param)='')">  
                        <xsl:text>#{ format(</xsl:text>
                        <xsl:value-of select="$param"/>
                        <xsl:text>.maxeu , '</xsl:text> 
                        <xsl:choose>
                            <xsl:when test="not(normalize-space($format)='')">
                                <xsl:value-of select="$format"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>%3.0f</xsl:text>
                            </xsl:otherwise> 
                        </xsl:choose>                                    
                        <xsl:text>') :default 100}</xsl:text> 
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:text>100</xsl:text>
                    </xsl:otherwise> 
                </xsl:choose>  
            </xsl:attribute>              
        </text> 
        <text x="125" fill="#eee"  style="text-anchor: middle; font-size: 8;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_textcenterval_</xsl:text>  
                <xsl:value-of select="$preff"/>
                <xsl:text>_pos</xsl:text> 
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 105"/>                            
            </xsl:attribute>    
            <xsl:attribute name="text">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($param)='')">  
                        <xsl:text>#{ format((</xsl:text>
                        <xsl:value-of select="$param"/>
                        <xsl:text>.maxeu -</xsl:text>
                        <xsl:value-of select="$param"/>
                        <xsl:text>.mineu) /2 , '</xsl:text> 
                        <xsl:choose>
                            <xsl:when test="not(normalize-space($format)='')">
                                <xsl:value-of select="$format"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>%3.0f</xsl:text>
                            </xsl:otherwise> 
                        </xsl:choose>                                    
                        <xsl:text>') :default 50}</xsl:text>
                    </xsl:when> 
                    <xsl:otherwise>
                        <xsl:text>50</xsl:text>
                    </xsl:otherwise> 
                </xsl:choose>  
            </xsl:attribute>              
        </text>         
        <elib:slider x="3" height="12" width="244" color1="#111" fillcolor1="#0e0" gradient-type="lr"> 
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_slider_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_sp</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="param">
                <xsl:value-of select="$param-sp"/>                            
            </xsl:attribute>
            <!--xsl:attribute name="environment">    
                 <xsl:value-of select="$еnvironment"/>
            </xsl:attribute-->
            <xsl:attribute name="fillenvironment">            
                <xsl:value-of select="$fillеnvironment"/>
            </xsl:attribute>           
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 82"/>                            
            </xsl:attribute> 
            <xsl:attribute name="disable">
                <xsl:choose>
                    <xsl:when test="not(normalize-space($disable)='')">  
                        <xsl:value-of select="$disable"/> 
                    </xsl:when> 
                </xsl:choose>
            </xsl:attribute>
            <!--xsl:attribute name="fillcolor1">
                <xsl:value-of select="$color"/>                            
            </xsl:attribute--> 
            <!--xsl:attribute name="fillcolor2">
                <xsl:value-of select="$color2"/>                            
            </xsl:attribute-->
            <xsl:attribute name="slidercolor2">
                <xsl:value-of select="$color"/>                            
            </xsl:attribute> 
            <xsl:attribute name="slidercolor1">
                <xsl:text>#a00</xsl:text>                             
            </xsl:attribute>
        </elib:slider>  

        <elib:rect x="15" height="5" width="220" color1="#111" fillcolor1="#0e0" stroke="#000" r="1" stroke-width="0.5"> 
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_</xsl:text> 
                <xsl:value-of select="$preff"/>
            </xsl:attribute>  
            <xsl:attribute name="param">
                <xsl:value-of select="$param"/>                            
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 72"/>                            
            </xsl:attribute> 
            <!--xsl:attribute name="environment">    
                 <xsl:value-of select="$еnvironment"/>
            </xsl:attribute-->
            <xsl:attribute name="fillenvironment">            
                <xsl:value-of select="$fillеnvironment"/>
            </xsl:attribute>             
            <!--xsl:attribute name="fillcolor1">
                <xsl:value-of select="$color"/>                            
            </xsl:attribute--> 
            <!--xsl:attribute name="fillcolor2">
                <xsl:value-of select="$color2"/>                            
            </xsl:attribute--> 
        </elib:rect>
        <text x="9"  fill="#eee" style="font-size: 11;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_text_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_spheader</xsl:text> 
            </xsl:attribute> 
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 28"/>                            
            </xsl:attribute>   
            <xsl:attribute name="text">
                <xsl:text>#{ !!</xsl:text>
                <xsl:value-of select="$param"/>
                <xsl:text>.comment ? (</xsl:text> 
                <xsl:value-of select="$param"/>
                <xsl:text>.comment) : '</xsl:text>
                <xsl:value-of select="$headerparam"/> 
                <xsl:text>' :default </xsl:text>
                <xsl:value-of select="$headerparam"/>
                <xsl:text>}</xsl:text>
            </xsl:attribute>                              
        </text>   
        <text x="136"  fill="#eee" style="font-size: 11;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_text_</xsl:text>
                <xsl:value-of select="$preff"/>
                <xsl:text>_spvalue</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 28"/>                            
            </xsl:attribute>   
            <xsl:attribute name="text">
                <xsl:text>#{ !!</xsl:text>
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.comment ? (</xsl:text> 
                <xsl:value-of select="$param-sp"/>
                <xsl:text>.comment) : '</xsl:text>
                <xsl:value-of select="$headerparam-sp"/> 
                <xsl:text>' :default </xsl:text>
                <xsl:value-of select="$headerparam-sp"/>
                <xsl:text>}</xsl:text>
            </xsl:attribute>            
        </text>  
        <text x="15" fill="#eee" style="font-size: 11;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_text_</xsl:text>  
                <xsl:value-of select="$preff"/>
                <xsl:text>_pos</xsl:text> 
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 67"/>                            
            </xsl:attribute>    
            <xsl:attribute name="text">
                <xsl:text>#{ !!</xsl:text>
                <xsl:value-of select="$param"/>
                <xsl:text>.comment ? (</xsl:text> 
                <xsl:value-of select="$param"/>
                <xsl:text>.comment) : '</xsl:text>
                <xsl:value-of select="$headerparam"/> 
                <xsl:text>' :default </xsl:text>
                <xsl:value-of select="$headerparam"/>
                <xsl:text>}</xsl:text>
            </xsl:attribute>              
        </text> 
        <text x="9" fill="#eee" style="font-size: 12;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_text_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_name</xsl:text>
            </xsl:attribute>   
            <xsl:attribute name="y">
                <xsl:value-of select="$shift + 12"/>                            
            </xsl:attribute> 
            <xsl:attribute name="text">
                <xsl:value-of select="$header"/>                            
            </xsl:attribute>              
        </text>

    </xsl:template> 
    
    <xsl:template name="elib_regulator_autocontrol">
        <xsl:param name="shift"/>
        <xsl:param name="preff"/>        
        <xsl:param name="param"/>
        <svgrect x="5" y="171" height="55" width="240" fill="#333" stroke="#ccc" stroke-width="1" r="4">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_autobackground_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_name</xsl:text>
            </xsl:attribute> 
        </svgrect>  
        <text x="9" y="181" text="Автоват/Дистанция" fill="#eee" style="font-size: 11;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_autoheader_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_name</xsl:text>
            </xsl:attribute>             
        </text>  
        <elib:button x="65" y="185" height="35" width="35" caption="Д" r="4"  kind="green" fontstyle="font-size: 13; fill: #eee;" offfontstyle="font-size: 13; fill: #eee;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_auto_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_buttonauto</xsl:text>
            </xsl:attribute>        
            <xsl:attribute name="param">
                <xsl:value-of select="$param"/>
                <xsl:text> @ 0</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="state">                
                <xsl:value-of select="$param"/>
            </xsl:attribute>             
        </elib:button>         
        <elib:button x="150" y="185" height="35" width="35" caption="А" r="4" kind="green"  fontstyle="font-size: 13; fill: #eee;" offfontstyle="font-size: 13; fill: #eee;">
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_auto_</xsl:text> 
                <xsl:value-of select="$preff"/>
                <xsl:text>_buttonlocal</xsl:text>
            </xsl:attribute>   
            <xsl:attribute name="param">
                <xsl:value-of select="$param"/>
                <xsl:text> @ 1</xsl:text>
            </xsl:attribute>  
            <xsl:attribute name="state">
                <xsl:text>!</xsl:text>
                <xsl:value-of select="$param"/>
            </xsl:attribute>            
        </elib:button>
    </xsl:template>    
    
    <xsl:template name="elib_regulator_cursor">
        <xsl:attribute name="cursor">
            <xsl:choose>
                <xsl:when test="not(normalize-space(@param-sp)='') and not(normalize-space(@actuator-sp)='')">                  
                    <xsl:text>pointer</xsl:text>    
                </xsl:when>  
                <xsl:when test="not(normalize-space(@actuator-sp)='')">                  
                    <xsl:text>pointer</xsl:text>    
                </xsl:when> 
                <xsl:when test="not(normalize-space(@param-sp)='')">                  
                    <xsl:text>pointer</xsl:text>    
                </xsl:when>                 
                <xsl:otherwise>
                    <xsl:text>none</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>          
    </xsl:template> 
    
    <xsl:template name="elib_regulator_event">
        <xsl:choose>
            <xsl:when test="not(normalize-space(@param-sp)='') and not(normalize-space(@actuator-sp)='')">                  
                <xsl:attribute name="onclick">
                    <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                    <xsl:text>if (event.button==0) eleclib.regulator_click(this,null) </xsl:text> 
                    <!--xsl:call-template name="elib_config_list_check"/-->
                    <xsl:text>} </xsl:text>                     
                </xsl:attribute>    
            </xsl:when>  
            <xsl:when test="not(normalize-space(@actuator-sp)='') or not(normalize-space(@param-sp)='')">                  
                <xsl:attribute name="onclick">
                    <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                    <xsl:text>if (event.button==0) eleclib.regulator_click(this,true) </xsl:text> 
                    <!--xsl:call-template name="elib_config_list_check"/-->
                    <xsl:text>} </xsl:text>                       
                </xsl:attribute>    
            </xsl:when>            
        </xsl:choose>
    </xsl:template> 
    
    <xsl:template name="apply_elib_regulator_popup">
        <defs>           
            <svg width="100%" height="100%"> 
                <xsl:attribute name="id">
                    <xsl:value-of select="@id"/>
                    <xsl:text>_popup</xsl:text>
                </xsl:attribute>   
                
                <xsl:variable name="popupbody">
                    <svgrect x="5" y="5" height="50" width="240" fill="#333" stroke="#ccc" stroke-width="1" r="4">
                        <xsl:attribute name="id">
                            <xsl:value-of select="@id"/>
                            <xsl:text>_sensor_head</xsl:text>                            
                        </xsl:attribute>                             
                    </svgrect> 
                    <text y="35" x="120" fill="#eee"  style="text-anchor: middle; font-size: 14;">
                        <xsl:attribute name="id">
                            <xsl:value-of select="@id"/>
                            <xsl:text>__sensor_headtext</xsl:text>  
                        </xsl:attribute>  
                        <xsl:attribute name="text">
                            <xsl:value-of select="@header"/>                         
                        </xsl:attribute>                         
                    </text> 
    
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@param-sp)='') and not(normalize-space(@actuator-sp)='') and not(normalize-space(@auto)='')">                    
                            <xsl:call-template name="elib_regulator_control"> 
                                <xsl:with-param name="shift" select="58"/>
                                <xsl:with-param name="preff">param</xsl:with-param>
                                <xsl:with-param name="param" select="@param"/>
                                <xsl:with-param name="param-sp" select="@param-sp"/>
                                <xsl:with-param name="format" select="@param-format"/>
                                <xsl:with-param name="header">Управление регулятором</xsl:with-param>
                                <xsl:with-param name="headerparam">Параметер</xsl:with-param>
                                <xsl:with-param name="headerparam-sp">Задание</xsl:with-param>
                                <xsl:with-param name="fillеnvironment">
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@param-environment)='')">
                                            <xsl:value-of select="@param-environment"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>light_green</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>
                                <xsl:with-param name="еnvironment">dark_fill</xsl:with-param>  
                                <xsl:with-param name="color">       
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@param-color)='')">
                                            <xsl:value-of select="@param-color"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#00d</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>                                    
                                </xsl:with-param>
                                <xsl:with-param name="color2"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@param-color2)='')">
                                            <xsl:value-of select="@param-color2"/>
                                        </xsl:when> 
                                    </xsl:choose>
                                </xsl:with-param>                                  
                            </xsl:call-template> 
                            <xsl:call-template name="elib_regulator_autocontrol"> 
                                <xsl:with-param name="shift" select="162"/>
                                <xsl:with-param name="preff">autoset</xsl:with-param>
                                <xsl:with-param name="param" select="@auto"/>                        
                            </xsl:call-template>                             
                            <xsl:call-template name="elib_regulator_control"> 
                                <xsl:with-param name="shift" select="230"/>
                                <xsl:with-param name="preff">actuator</xsl:with-param>
                                <xsl:with-param name="param" select="@actuator"/>
                                <xsl:with-param name="param-sp" select="@actuator-sp"/>
                                <xsl:with-param name="format" select="@actuator-format"/>
                                <xsl:with-param name="header">Управление ИМ</xsl:with-param>
                                <xsl:with-param name="headerparam">Положение ИМ</xsl:with-param>
                                <xsl:with-param name="headerparam-sp">Задание ИМ</xsl:with-param>     
                                <xsl:with-param name="disable" select="@auto"/>  
                                <xsl:with-param name="fillеnvironment">
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@actuator-еnvironment)='')">
                                            <xsl:value-of select="@actuator-еnvironment"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>light_green</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>
                                <xsl:with-param name="еnvironment">dark_gray</xsl:with-param>                               
                                <xsl:with-param name="color"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@actuator-color)='')">
                                            <xsl:value-of select="@param-color"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#0e0</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param> 
                                <xsl:with-param name="color2"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@actuator-color2)='')">
                                            <xsl:value-of select="@param-color2"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#0a0</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>                                
                            </xsl:call-template>                             
                        </xsl:when> 
                        <xsl:when test="not(normalize-space(@actuator-sp)='')">                    
                            <xsl:call-template name="elib_regulator_control"> 
                                <xsl:with-param name="shift" select="58"/>
                                <xsl:with-param name="preff">actuator</xsl:with-param>
                                <xsl:with-param name="param" select="@actuator"/>
                                <xsl:with-param name="param-sp" select="@actuator-sp"/>
                                <xsl:with-param name="format" select="@actuator-format"/>
                                <xsl:with-param name="header">Управление ИМ</xsl:with-param>
                                <xsl:with-param name="headerparam">Положение ИМ</xsl:with-param>
                                <xsl:with-param name="headerparam-sp">Задание ИМ</xsl:with-param> 
                                <xsl:with-param name="fillеnvironment">
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@actuator-еnvironment)='')">
                                            <xsl:value-of select="@actuator-еnvironment"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>light_green</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>
                                <xsl:with-param name="еnvironment">dark_gray</xsl:with-param>                             
                                <xsl:with-param name="color"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@actuator-color)='')">
                                            <xsl:value-of select="@actuator-color"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#0e0</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>
                                <xsl:with-param name="color2"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@actuator-color2)='')">
                                            <xsl:value-of select="@actuator-color2"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#0a0</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>  
                            </xsl:call-template> 
                        </xsl:when>       
                        <xsl:when test="not(normalize-space(@param-sp)='')">                    
                            <xsl:call-template name="elib_regulator_control"> 
                                <xsl:with-param name="shift" select="58"/>
                                <xsl:with-param name="preff">param</xsl:with-param>
                                <xsl:with-param name="param" select="@param"/>
                                <xsl:with-param name="param-sp" select="@param-sp"/>
                                <xsl:with-param name="format" select="@param-format"/>
                                <xsl:with-param name="header">Управление регулятором</xsl:with-param>
                                <xsl:with-param name="headerparam">Значение</xsl:with-param>
                                <xsl:with-param name="headerparam-sp">Задание </xsl:with-param> 
                                <xsl:with-param name="fillеnvironment">
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@param-environment)='')">
                                            <xsl:value-of select="@param-environment"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>light_green</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>
                                <xsl:with-param name="еnvironment">dark_gray</xsl:with-param>  
                                <xsl:with-param name="color"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@param-color)='')">
                                            <xsl:value-of select="@param-color"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#0e0</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>
                                <xsl:with-param name="color2"> 
                                    <xsl:choose>
                                        <xsl:when test="not(normalize-space(@param-color2)='')">
                                            <xsl:value-of select="@param-color2"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:text>#0a0</xsl:text>
                                        </xsl:otherwise> 
                                    </xsl:choose>
                                </xsl:with-param>  
                            </xsl:call-template> 
                        </xsl:when>                          
                    </xsl:choose>                    
                </xsl:variable> 
                    
                
                <xsl:for-each select="exsl:node-set($popupbody)/*">
                    <xsl:choose>
                        <xsl:when test="local-name()='button'">
                            <xsl:call-template name="elib_button"/>
                        </xsl:when>
                        <xsl:when test="local-name()='rect'">
                            <xsl:call-template name="elib_rect"/>
                        </xsl:when> 
                        <xsl:when test="local-name()='sensor'">
                            <xsl:call-template name="elib_sensor"/>
                        </xsl:when> 
                        <xsl:when test="local-name()='slider'">
                            <xsl:call-template name="elib_slider"/>
                        </xsl:when>    
                        <xsl:when test="local-name()='text'">
                            <xsl:call-template name="svg_text"/>
                        </xsl:when>
                        <xsl:when test="local-name()='svgrect'">
                            <xsl:call-template name="svg_rect"/>
                        </xsl:when>
                        <xsl:when test="local-name()='line'">
                            <xsl:call-template name="svg_line"/>
                        </xsl:when>   
                    </xsl:choose>
                </xsl:for-each>           
                
            </svg>            
        </defs>  
    </xsl:template>               
    

    
    <xsl:template match="//elib:regulator">
        <g>  
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_elib_schema"/>
            <xsl:attribute name="period">            
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@period)='')"> 
                        <xsl:value-of select="@period"/>
                    </xsl:when>  
                    <xsl:otherwise>
                        <xsl:text>600</xsl:text>
                    </xsl:otherwise>                
                </xsl:choose> 
            </xsl:attribute> 
            <xsl:call-template name="apply_svg_g_visible_binding"/> 
            <xsl:call-template name="apply_title">
                <xsl:with-param name="title" select="@header"/>
            </xsl:call-template> 
            <xsl:attribute name="isinvisibleelement">
                <xsl:text>true</xsl:text>
            </xsl:attribute>
            <xsl:call-template name="apply_rect"/> 
            <xsl:choose>
                <xsl:when test="not(normalize-space(@param)='') and not(normalize-space(@actuator)='')">
                    <xsl:attribute name="charts">
                        <xsl:text>['</xsl:text> 
                        <xsl:value-of select="@param"/>
                        <xsl:text>' , '</xsl:text>
                        <xsl:value-of select="@actuator"/>
                        <xsl:text>']</xsl:text> 
                    </xsl:attribute>  
                    <xsl:attribute name="colors">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@param-color)='') and not(normalize-space(@actuator-color)='')">
                                <xsl:text>['</xsl:text>
                                <xsl:value-of select="@param-color"/>
                                <xsl:text>','</xsl:text>
                                <xsl:value-of select="@actuator-color"/>
                                <xsl:text>']</xsl:text>
                            </xsl:when>
                            <xsl:when test="not(normalize-space(@param-color)='')">
                                <xsl:text>['</xsl:text>
                                <xsl:value-of select="@param-color"/>
                                <xsl:text>','#0e0']</xsl:text>
                            </xsl:when>
                            <xsl:when test="not(normalize-space(@actuator-color)='')">
                                <xsl:text>['#00d','</xsl:text>
                                <xsl:value-of select="@actuator-color"/>
                                <xsl:text>']</xsl:text>
                            </xsl:when>                            
                            <xsl:otherwise>
                                <xsl:text>['#00d','#0e0']</xsl:text>
                            </xsl:otherwise> 
                        </xsl:choose>
                    </xsl:attribute>                     
                </xsl:when> 
                <xsl:when test="not(normalize-space(@actuator)='')">
                    <xsl:attribute name="charts">
                        <xsl:text>['</xsl:text> 
                        <xsl:value-of select="@actuator"/>
                        <xsl:text>']</xsl:text> 
                    </xsl:attribute>  
                    <xsl:attribute name="colors">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@actuator-color)='')">
                                <xsl:text>['</xsl:text>
                                <xsl:value-of select="@actuator-color"/>
                                <xsl:text>']</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>['#0e0']</xsl:text>
                            </xsl:otherwise> 
                        </xsl:choose>
                    </xsl:attribute>                     
                </xsl:when> 
                <xsl:when test="not(normalize-space(@param)='')">
                    <xsl:attribute name="charts">
                        <xsl:text>['</xsl:text> 
                        <xsl:value-of select="@param"/>
                        <xsl:text>']</xsl:text> 
                    </xsl:attribute>  
                    <xsl:attribute name="colors">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@param-color)='')">
                                <xsl:text>['</xsl:text>
                                <xsl:value-of select="@param-color"/>
                                <xsl:text>']</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>['#00d']</xsl:text>
                            </xsl:otherwise> 
                        </xsl:choose>
                    </xsl:attribute>                     
                </xsl:when>                
            </xsl:choose>
            <xsl:choose>
                <xsl:when test="not(normalize-space(@period)='')"> 
                    <xsl:attribute name="period"> 
                        <xsl:value-of select="@period"/>
                    </xsl:attribute>                 
                </xsl:when>                
            </xsl:choose>                
            
            <xsl:call-template name="elib_regulator_event"/>
            <xsl:call-template name="elib_regulator_cursor"/>
            <xsl:call-template name="apply_elib_regulator_popup"/>
            <xsl:call-template name="elib_config_popup"/>
                     
            <svg>                   
                <xsl:call-template name="apply_rect"/>  
                <rect style="fill: white; stroke : white; opacity: 0">                 
                    <xsl:call-template name="apply_0_0_width_height"/>
                </rect>
            </svg>    
        </g>        
    </xsl:template>            
    
</xsl:stylesheet>
