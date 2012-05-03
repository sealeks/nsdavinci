<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:mlib="http://dvnci/mlib"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:exsl="http://xmlsoft.org/XSLT/namespace">
    
    

    <xsl:template name="mainlib">  
        <script type="text/javascript" xlink:href="../libs/main/js/mainlib.js"></script>   
    </xsl:template>
    
      
    <xsl:template name="apply_mlib_schema">    
        <!--xsl:attribute name="xsi:schemaLocation">
            <xsl:text>../libs/main/maillib.xsd</xsl:text>
        </xsl:attribute-->  
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
 
 
    <xsl:template name="apply_mlib_araturatype_motor">    
        <circle cx="500" cy="500" r="300" stroke-width="20"/>
        <path d="M 400,600 L 400,400 L 500,500 L 600,400 L 600,600" stroke-width="30"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_araturatype_motorD">    
        <circle cx="500" cy="500" r="300" stroke-width="20"/>
        <path d="M 400,450 L 400,550 L 550,550 L 550,600 L 650,500 L 550,400 L 550,450z" stroke-width="20"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_araturatype_simple">    
        <path d="M 200,350 L 200,650 L 800,350 L 800,650 z" stroke-width="20"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_araturatype_cvalve">    
        <path d="M 200,500 L 200,800 L 800,500 L 800,800 z" stroke-width="20"/>
        <path d="M 350,220 L 650, 220 L 650,320 L 350, 320z" stroke-width="20"/>  
        <path d="M 500,650 L 500, 550 L 600,500 L 400, 450 L 600, 400 L 500,350 L 500, 320" fill="none" stroke-width="20"/>
        <line x1="700" y1="300" x2="700" y2="500" stroke-width="20"/>
        <line x1="700" y1="500" x2="650" y2="400" stroke-width="20"/>
        <line x1="700" y1="500" x2="750" y2="400" stroke-width="20"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_araturatype_ovalve">    
        <path d="M 200,500 L 200,800 L 800,500 L 800,800 z" stroke-width="20"/>
        <path d="M 350,220 L 650, 220 L 650,320 L 350, 320z" stroke-width="20"/>  
        <path d="M 500,650 L 500, 550 L 600,500 L 400, 450 L 600, 400 L 500,350 L 500, 320" fill="none" stroke-width="20"/>
        <line x1="700" y1="300" x2="700" y2="500" stroke-width="20"/>
        <line x1="700" y1="300" x2="650" y2="400" stroke-width="20"/>
        <line x1="700" y1="300" x2="750" y2="400" stroke-width="20"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_araturatype_rvalve">    
        <path d="M 200,500 L 200,800 L 800,500 L 800,800 z" stroke-width="20"/> 
        <path d="M 500,650 L 500, 360" fill="none" stroke-width="20"/>
        <path d="M 410 ,360 L 590, 360 L 500,220 z"  stroke-width="20"/>
    </xsl:template> 
    
    
    <xsl:template name="apply_mlib_araturatype_bolt">    
        <path d="M 200,500 L 200,800 L 800,500 L 800,800 z" stroke-width="20"/> 
        <path d="M 500,650 L 500, 380" fill="none" stroke-width="20"/>
        <circle cx="500" cy="320" r="120" stroke-width="20"/>
        <path d="M 450 370 L 450 270 L 500 320 L 550 270 L 550 370" stroke-width="20" fill="none"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_araturatype_regul">    
        <path d="M 200,500 L 200,800 L 800,500 L 800,800 z" stroke-width="20"/> 
        <path d="M 500,650 L 500, 380" fill="none" stroke-width="20"/>
        <circle cx="500" cy="320" r="120" stroke-width="20"/>
        <path d="M 450 370 L 450 270 L 500 320 L 550 270 L 550 370" stroke-width="20" fill="none"/>
    </xsl:template>
    

    
    <xsl:template name="apply_mlib_araturatype"> 
        <xsl:choose>                         
            <xsl:when test="boolean(@type) and not(normalize-space(@type)='')">                             
                <xsl:choose>
                    <xsl:when test="@type='cvalve'"> 
                        <xsl:call-template name="apply_mlib_araturatype_cvalve"/>
                    </xsl:when>
                    <xsl:when test="@type='ovalve'"> 
                        <xsl:call-template name="apply_mlib_araturatype_ovalve"/>
                    </xsl:when>
                    <xsl:when test="@type='rvalve'">
                        <xsl:call-template name="apply_mlib_araturatype_rvalve"/> 
                    </xsl:when> 
                    <xsl:when test="@type='bolt'">
                        <xsl:call-template name="apply_mlib_araturatype_bolt"/> 
                    </xsl:when>
                    <xsl:when test="@type='motorD'">
                        <xsl:call-template name="apply_mlib_araturatype_motorD"/> 
                    </xsl:when> 
                    <xsl:when test="@type='simple'">
                        <xsl:call-template name="apply_mlib_araturatype_simple"/> 
                    </xsl:when>
                    <xsl:when test="@type='regul'">
                        <xsl:call-template name="apply_mlib_araturatype_regul"/> 
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:call-template name="apply_mlib_araturatype_motor"/> 
                    </xsl:otherwise>                     
                </xsl:choose>
            </xsl:when> 
            <xsl:otherwise>
                <xsl:call-template name="apply_mlib_araturatype_motor"/> 
            </xsl:otherwise>                           
        </xsl:choose>    
    
    </xsl:template>
    
     <!--
    
    Отображение аттоибута cursor
    
    -->  
    
    
    <xsl:template name="apply_mlib_aratura_cursor_dsbl">
        <xsl:attribute name="cursor">
            <xsl:text>none</xsl:text>
        </xsl:attribute>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_aratura_cursor_checkstatevalid">
        <xsl:choose>                        
            <xsl:when test="(boolean(@off) and not(normalize-space(@off)='')) and (boolean(@on) and not(normalize-space(@on)=''))">
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
    

    <xsl:template name="apply_mlib_aratura_cursor_autocontrol">
        <xsl:attribute name="cursor">
            <xsl:text>#{ </xsl:text>
            <xsl:call-template name="apply_mlib_aratura_cursor_checkstatevalid"/>
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
    
    
    <xsl:template name="apply_mlib_aratura_cursor_auto">
        <xsl:attribute name="cursor">
            <xsl:text>#{ </xsl:text>
            <xsl:call-template name="apply_mlib_aratura_cursor_checkstatevalid"/>
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
    
    
    <xsl:template name="apply_mlib_aratura_cursor_local">
        <xsl:attribute name="cursor">
            <xsl:text>#{ </xsl:text>
            <xsl:call-template name="apply_mlib_aratura_cursor_checkstatevalid"/>
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
    
    
    
    <xsl:template name="apply_mlib_aratura_cursor">
        <xsl:choose>                        
            <xsl:when test="(boolean(@off) and not(normalize-space(@off)='')) or (boolean(@on) and not(normalize-space(@on)=''))">
                <xsl:choose>                        
                    <xsl:when test="(boolean(@roff) and not(normalize-space(@roff)='')) or (boolean(@ron) and not(normalize-space(@ron)='')) or (boolean(@rauto) and not(normalize-space(@rauto)=''))">
                        <xsl:choose>                        
                            <xsl:when test="(boolean(@rauto) and not(normalize-space(@rauto)='')) and (boolean(@auto) and not(normalize-space(@auto)=''))">
                                <xsl:call-template name="apply_mlib_aratura_cursor_autocontrol"/>
                            </xsl:when>
                            <xsl:when test="(boolean(@auto) and not(normalize-space(@auto)=''))">
                                <xsl:call-template name="apply_mlib_aratura_cursor_auto"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:call-template name="apply_mlib_aratura_cursor_local"/>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:call-template name="apply_mlib_aratura_cursor_dsbl"/>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="apply_mlib_aratura_cursor_dsbl"/>
            </xsl:otherwise>        
        </xsl:choose>    
    </xsl:template>
    
    
    <!--
    
    Описание логики состояния 
    
    -->  
    
    
    <xsl:template name="apply_mlib_aratura_state"> 
        <g class="none">
            <xsl:variable name="envir"> 
                <xsl:choose>
                    <xsl:when test="boolean(@oncolor) and not(normalize-space(@oncolor)='')"> 
                        <xsl:text>__</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_armatclass</xsl:text>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="@environment"/> 
                    </xsl:otherwise>
                </xsl:choose>                
            </xsl:variable>
            <xsl:choose>                              
                <xsl:when test="boolean(@filter) and not(@filter='')">
                    <xsl:attribute name="filter">
                        <xsl:text>url(#filter_lib_armat1000)</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose> 
            <xsl:choose>                        
                <xsl:when test="(boolean(@on) and not(normalize-space(@on)='')) and (boolean(@off) and not(normalize-space(@off)=''))"> 
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
                            <xsl:value-of select="$envir"/>
                            <xsl:text>;off</xsl:text>
                            <xsl:value-of select="$envir"/>
                            <xsl:text>;' : </xsl:text>
                                
                                
                            <xsl:text>'on</xsl:text>
                            <xsl:value-of select="$envir"/>
                            <xsl:text>;off</xsl:text>
                            <xsl:value-of select="$envir"/>
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
                        <xsl:value-of select="$envir"/>
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
                        <xsl:value-of select="$envir"/>
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
            <xsl:call-template name="apply_mlib_araturatype"/> 
        </g>
    </xsl:template> 

    
    
    <!--
    
    Отображение состояния мест.
    
    -->
    
    <xsl:template name="apply_mlib_aratura_local_img">    
        <circle cx="150" cy="150" r="100" stroke-width="20"/>
        <path d="M 110,190 L 110,110 L 150,150 L 190,110 L 190,190" stroke-width="15"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_aratura_local">    
        <xsl:choose>
            <xsl:when test="boolean(@local) and not(normalize-space(@local)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@local"/>
                        <xsl:text> ? 'local'  : 'transparent' :default transparent }</xsl:text>
                    </xsl:attribute>                           
                    <xsl:call-template name="apply_mlib_aratura_local_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>  
    
    
    
    
    <!--
    
    Отображение состояния автоматический.
    
    -->
    
    <xsl:template name="apply_mlib_aratura_auto_img">    
        <circle cx="150" cy="150" r="100" stroke-width="20"/>
        <path d="M 110,190 L 150,110  L 190,190 M 140,150 L 160,150" stroke-width="15" fill="none"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_aratura_auto">    
        <xsl:choose>
            <xsl:when test="boolean(@auto) and not(normalize-space(@auto)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@auto"/>
                        <xsl:text> ? 'autocontrol'  : 'transparent' :default transparent }</xsl:text>
                    </xsl:attribute>                              
                    <xsl:call-template name="apply_mlib_aratura_auto_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>   
    
    
    
    <!--
    
    Отображение состояния автоматический.
    
    -->
    
    <xsl:template name="apply_mlib_aratura_control_img">    
        <circle cx="850" cy="150" r="60" stroke-width="0"/>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_aratura_control">    
        <xsl:choose>
            <xsl:when test="boolean(@control) and not(normalize-space(@control)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@control"/>
                        <xsl:text> ? 'oncheckcontrol'  : 'offcheckcontrol' :default oncheckcontrol }</xsl:text>
                    </xsl:attribute>                              
                    <xsl:call-template name="apply_mlib_aratura_control_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>      
    
    
    
    <!--
    
    Отображение сигналов открытия и закрытия
    
    -->
    
    
    <xsl:template name="apply_mlib_aratura_onsig">    
        <path d="M 450, 170 L 450,100 L 400,100 L 500,10  L 600,100 L 550,100 L 550,170z" stroke-width="0" stroke="none" fill="#0F0">
            <animate  attributeType="XML" attributeName="fill" values="#0F0;transparent;" keyTimes="0;.5" dur="500ms"  repeatCount="indefinite" calcMode="discrete"/>
        </path>
    </xsl:template>  
    
    <xsl:template name="apply_mlib_aratura_offsig">
        <path d="M 450, 10 L 450,80 L 400,80 L 500,170  L 600,80 L 550,80 L 550,10z" stroke-width="0" stroke="none" fill="#F00">
            <animate  attributeType="XML" attributeName="fill" values="transparent;#F00;" keyTimes="0;.5" dur="500ms"  repeatCount="indefinite" calcMode="discrete"/>
        </path>
    </xsl:template> 
    
    <xsl:template name="apply_mlib_aratura_sig">   
        <xsl:choose>                          
            <xsl:when test="boolean(@don) and not(normalize-space(@don)='')"> 
                <g>
                    <xsl:attribute name="style">
                        <xsl:choose>                          
                            <xsl:when test="boolean(@on) and not(normalize-space(@on)='')">                                               
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
                    <xsl:call-template name="apply_mlib_aratura_onsig"/>
                </g>
            </xsl:when>
        </xsl:choose> 
        <xsl:choose>
            <xsl:when test="boolean(@doff) and not(normalize-space(@doff)='')"> 
                <g>
                    <xsl:attribute name="style">
                        <xsl:choose>                          
                            <xsl:when test="boolean(@off) and not(normalize-space(@off)='')">                                                 
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
                    <xsl:call-template name="apply_mlib_aratura_offsig"/>
                </g>                    
            </xsl:when>                    
        </xsl:choose>                                                   
    </xsl:template> 
    
    
    <!--
    
    Отображение аварийности
    
    -->
    
    <xsl:template name="apply_mlib_aratura_alarmstate">    
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
    
    
    <xsl:template name="apply_mlib_aratura_event"> 
        <xsl:choose>             
            <xsl:when test="boolean(@rauto) or boolean(@roff) or boolean(@ron)">  
                <xsl:attribute name="onclick">
                    <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                            <xsl:text>mainlib.armatura_popup(this, '</xsl:text>
                            <xsl:value-of select="@rauto"/>                                                    
                            <xsl:text>');};</xsl:text>
                </xsl:attribute>                   
            </xsl:when>               
        </xsl:choose>
    </xsl:template>  
    
    <!--
    
    формирование стиля
    
    -->    
    
    
    <xsl:template name="apply_mlib_aratura_style">
        <defs>
            <style type="text/css">
                <xsl:text>  
            
                </xsl:text>
                <xsl:text>  g#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>[cursor="pointer"] {</xsl:text>
                <xsl:text>
                outline: 1px solid transparent;
                cursor: pointer;}
                </xsl:text>
            
                <xsl:text>  g#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>[cursor="pointer"]:hover {</xsl:text>
                <xsl:text>
                outline: 1px solid #40FF00;
                cursor: pointer;}
                </xsl:text>
            
                <xsl:text> 
                
                </xsl:text>
                <xsl:text>  g#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text> {</xsl:text>
                <xsl:text> 
              
               cursor: none;}
                </xsl:text>
            
            
                <xsl:text>  g#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>:hover {</xsl:text>
                <xsl:text> 
               
               cursor: none;}
                </xsl:text>
            
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
    </xsl:template>
    
    
   <xsl:template name="apply_mlib_aratura_popup">
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
            
            <xsl:variable name="armaturakind"> 
                    <xsl:choose>
                        <xsl:when test="not(boolean(@type)) or (@type='motorD') or (@type='motor') or (normalize-space(@type)='')">
                            <xsl:text>motor</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>valve</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>        
            </xsl:variable>
            
            <xsl:variable name="oncaption">
                    <xsl:choose>
                        <xsl:when test="($armaturakind='motor')">
                            <xsl:text>Пуск</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>Открыть</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>                
            </xsl:variable>
            
            <xsl:variable name="offcaption">
                    <xsl:choose>
                        <xsl:when test="($armaturakind='motor')">
                            <xsl:text>Стоп</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>Закрыть</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>                
            </xsl:variable> 
            
            <xsl:variable name="stopcaption">
                    <xsl:choose>
                        <xsl:when test="($armaturakind='motor')">
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
                <xsl:text> textsize: 12px ; fill: white; </xsl:text>    
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
                    <sensor x="5" y="10" width="190" height="80" color1="#333" color2="#555" caption="{@header}" alighn="center" fontcolor="#eee" r="10" stroke="#eee" stroke-width="1">
                    </sensor>
                    <xsl:choose>
                        <xsl:when test="$typecontrol='onoff'">
                            <button x="5" y="100" width="190" height="30" param="{@ron}" color1="#080" color2="#0B0" caption="{$oncaption}" disable="{$fullvalid}" r="5" fontstyle="{$fontstyle}">
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
                            <button x="5" y="133" width="190" height="30" param="{@roff}" color1="#888" color2="#BBB" oncolor1="#880" oncolor2="#BB0" caption="{$stopcaption}" disable="{$fullvalid}" r="5" fontstyle="{$fontstyle}">
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
                            <button x="5" y="164" width="190" height="30" param="{@roff}" color1="#800" color2="#B00" caption="{$offcaption}" disable="{$fullvalid}" r="5" fontstyle="{$fontstyle}">
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
                            <button x="5" y="100" width="190" height="90" param="{@ron}"  state="{@ron}" type="tumbler" caption="{$oncaption}" oncaption="{$offcaption}" color1="#080" color2="#0B0" oncolor1="#800" oncolor2="#B00" disable="{$fullvalid}" r="5">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button</xsl:text>
                                </xsl:attribute>                                
                            </button>
                        </xsl:when> 
                        <xsl:when test="$typecontrol='off'">
                            <button x="5" y="100" width="190" height="90" param="{@roff}" state="{@roff}" type="tumbler" caption="{$offcaption}" oncaption="{$oncaption}" oncolor1="#080" oncolor2="#0B0" color1="#800" color2="#B00" disable="{$fullvalid}" r="5">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button</xsl:text>
                                </xsl:attribute>
                            </button>    
                        </xsl:when> 
                    </xsl:choose>
                    
                    <xsl:choose>
                        <xsl:when test="not(normalize-space(@rauto)='')">
                            <button x="5" y="205" width="190" height="40" param="{@rauto}" state="{@rauto}" type="tumbler" caption="В автомат" oncaption="В дист." color1="#888" color2="#BBB" r="5">
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
                            <xsl:call-template name="mlib_button"/>
                        </xsl:when>
                        <xsl:when test="local-name()='rect'">
                            <xsl:call-template name="mlib_button"/>
                        </xsl:when> 
                        <xsl:when test="local-name()='sensor'">
                            <xsl:call-template name="mlib_sensor"/>
                        </xsl:when>                         
                    </xsl:choose>
                </xsl:for-each>    
                
           </svg>               
       </defs>                   
   </xsl:template>       
    
    
    
    
  
  
        <!--
    
    Основной обработчик
    
    -->
      
    
    <xsl:template match="//mlib:armatura" >   
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
            
            <xsl:call-template name="apply_mlib_schema"/>
                       
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <!--xsl:call-template  name="apply_visible"/-->
            
            <xsl:call-template name="apply_svg_g_visible"/> 
                                                                               
            <xsl:call-template name="apply_mlib_aratura_cursor"/>
                       
            <xsl:call-template name="apply_mlib_aratura_event"/>
            
            <xsl:call-template name="apply_mlib_aratura_style"/>
            
            <xsl:call-template name="apply_mlib_aratura_popup"/>

            <rect fill="white" stroke="white" opacity="0">
                <xsl:call-template name="apply_rect"/> 
            </rect>            
                        
            <svg viewBox="0 0 1000 1000" preserveAspectRatio="none"> 
            
                
                
                <xsl:call-template name="apply_rect"/>
                               
                <xsl:call-template name="apply_mlib_aratura_alarmstate"/>
             
                <xsl:call-template name="apply_mlib_aratura_state"/>
                
                <xsl:call-template name="apply_mlib_aratura_auto"/> 
                                
                <xsl:call-template name="apply_mlib_aratura_local"/>
                
                <xsl:call-template name="apply_mlib_aratura_control"/> 
                                
                <xsl:call-template name="apply_mlib_aratura_sig"/>

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
    
    
    <xsl:template name="apply_mlib_button_control"> 
    
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
    
    <xsl:template name="apply_mlib_button_state"> 
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
    
    
    <xsl:template name="apply_mlib_button_class">
        <xsl:variable name="buttonstyle">
            <xsl:value-of select="@id"/>
            <xsl:text>__mlibbuttonstyle</xsl:text>
        </xsl:variable>
        <xsl:attribute name="class">
            <xsl:value-of select="$buttonstyle"/>
        </xsl:attribute> 
    </xsl:template>
    
 
    <xsl:template name="apply_mlib_button_style">
        
        <xsl:variable name="buttonstyle"> 
            <xsl:text>.</xsl:text>
            <xsl:value-of select="@id"/>
            <xsl:text>__mlibbuttonstyle</xsl:text>
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
        <xsl:variable name="mainselector_id"> 
            <xsl:text>g#</xsl:text>
            <xsl:value-of select="@id"/>
            <xsl:text disable-output-escaping="yes"> svg</xsl:text>
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
        
        <xsl:variable name="var_fontstyle">
            <xsl:choose>
                <xsl:when test="(boolean(@fontstyle) and not(normalize-space(@fontstyle)=''))">
                    <xsl:value-of select="@fontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>
                 font-size: 18;
                 fill: white;
                 font-weight: bold;
                    </xsl:text>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable>
        
        <xsl:variable name="var_offfontstyle">
            <xsl:choose>
                <xsl:when test="(boolean(@offfontstyle) and not(normalize-space(@offfontstyle)=''))">
                    <xsl:value-of select="@offfontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$var_fontstyle"/>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable> 
        
        <xsl:variable name="var_dsblfontstyle">
            <xsl:choose>
                <xsl:when test="(boolean(@dsblfontstyle) and not(normalize-space(@dsblfontstyle)=''))">
                    <xsl:value-of select="@dsblfontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>
                 font-size: 18;
                 fill: #666;
                    </xsl:text>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable>
        
        <style type="text/css">
            <xsl:text>
                
            </xsl:text>
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text>  text</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:value-of select="$var_fontstyle"/>      
            <xsl:choose> 
                <xsl:when test="boolean(@alighn='left')"> 
                    <xsl:text>text-anchor: start;</xsl:text>
                </xsl:when>
                <xsl:when test="boolean(@alighn='right')"> 
                    <xsl:text>text-anchor: end;</xsl:text>
                </xsl:when>
                <xsl:otherwise> 
                    <xsl:text>text-anchor: middle;</xsl:text>
                </xsl:otherwise> 
            </xsl:choose>
            <xsl:text disable-output-escaping="yes">
                 dominant-baseline: central; 
                 -webkit-user-select: none;}
                 
            </xsl:text> 
               
            <xsl:value-of select="$mainselector_id"/>  
            <xsl:text disable-output-escaping="yes">[state="off"] > svg >  text</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:value-of select="$var_offfontstyle"/>   
            <xsl:text>;}
           
            </xsl:text>
                 
            <xsl:value-of select="$mainselector_id"/>  
            <xsl:text disable-output-escaping="yes">[state="disable"] > svg >  text</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:value-of select="$var_dsblfontstyle"/>   
            <xsl:text>;}
           
            </xsl:text>
       
     
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text> *</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text>{
                cursor: pointer;}
          
            </xsl:text> 
            
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text>[state="disable"] *</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text>{
                cursor: default;}
          
            </xsl:text>    
            
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes"> > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
                fill: transparent;}
                 
            </xsl:text>    
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
            <xsl:text disable-output-escaping="yes">:hover > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {               
                -webkit-svg-shadow: 3px 3px  3px rgba(0, 0, 0, 0.5);}
         
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
                -webkit-svg-shadow: 0px 0px 0px rgba(0, 0, 0, 0);} 
                 
            </xsl:text> 
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes"> > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:text>
                stroke: 
            </xsl:text>
            <xsl:value-of select="$var_color1"/>
            <xsl:text >;
                stroke-width: 1;}   
                    
            </xsl:text>    
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes">:hover > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:text>
                stroke: 
            </xsl:text>
            <xsl:value-of select="$var_color2"/>
            <xsl:text >;
                stroke-width: 1;}                  
       
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
            <xsl:text disable-output-escaping="yes">[state="off"] > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:text>
                stroke: 
            </xsl:text>
            <xsl:value-of select="$var_oncolor2"/>
            <xsl:text >;
                stroke-width: 1;}   
                    
            </xsl:text>    
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes">[state="off"]:hover > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
            </xsl:text>
            <xsl:text>
                stroke: 
            </xsl:text>
            <xsl:value-of select="$var_oncolor1"/>
            <xsl:text >;
                stroke-width: 1;}            
           
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
            <xsl:text disable-output-escaping="yes"> 
                -webkit-svg-shadow: 0px 0px 0px rgba(0, 0, 0, 0);} 
                
            </xsl:text> 
                
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes">[state="disable"] > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> , </xsl:text>
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes">[state="disable"]:hover > g > rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> , </xsl:text>
            <xsl:value-of select="$mainselector_id"/>
            <xsl:text disable-output-escaping="yes">[state="disable"]:active > g >rect</xsl:text>
            <xsl:value-of select="$buttonstyle"/>
            <xsl:text> {
                 stroke-width: 0;
                 stroke: none;}
                 
                 
            </xsl:text>  
        </style>
        
        <defs>
            <linearGradient x1="100%" y1="0%" x2="100%" y2="100%">
                <xsl:attribute name="id">
                    <xsl:value-of select="$gradienton_id"/>
                </xsl:attribute>   
                <stop offset="0%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_color1"/>
                    </xsl:attribute>                         
                </stop>
                <stop offset="50%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_color2"/>
                    </xsl:attribute>                         
                </stop> 
                <stop offset="100%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_color1"/>
                    </xsl:attribute>                         
                </stop>
            </linearGradient>
            
            <linearGradient x1="100%" y1="0%" x2="100%" y2="100%">
                <xsl:attribute name="id">
                    <xsl:value-of select="$gradientona_id"/>
                </xsl:attribute>   
                <stop offset="0%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_color2"/>
                    </xsl:attribute>                         
                </stop>
                <stop offset="50%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_color1"/>
                    </xsl:attribute>                         
                </stop> 
                <stop offset="100%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_color2"/>
                    </xsl:attribute>                         
                </stop>
            </linearGradient>
            
            <linearGradient x1="100%" y1="0%" x2="100%" y2="100%">
                <xsl:attribute name="id">
                    <xsl:value-of select="$gradientoff_id"/>
                </xsl:attribute>   
                <stop offset="0%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_oncolor1"/>
                    </xsl:attribute>                         
                </stop>
                <stop offset="50%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_oncolor2"/>
                    </xsl:attribute>                         
                </stop> 
                <stop offset="100%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_oncolor1"/>
                    </xsl:attribute>                         
                </stop>
            </linearGradient>
            
            <linearGradient x1="100%" y1="0%" x2="100%" y2="100%">
                <xsl:attribute name="id">
                    <xsl:value-of select="$gradientoffa_id"/>
                </xsl:attribute>   
                <stop offset="0%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_oncolor2"/>
                    </xsl:attribute>                         
                </stop>
                <stop offset="50%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_oncolor1"/>
                    </xsl:attribute>                         
                </stop> 
                <stop offset="100%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_oncolor2"/>
                    </xsl:attribute>                         
                </stop>
            </linearGradient> 
            
            <linearGradient x1="100%" y1="0%" x2="100%" y2="100%">
                <xsl:attribute name="id">
                    <xsl:value-of select="$gradientdsbl_id"/>
                </xsl:attribute>   
                <stop offset="0%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_dsblcolor1"/>
                    </xsl:attribute>                         
                </stop>
                <stop offset="50%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_dsblcolor2"/>
                    </xsl:attribute>                         
                </stop> 
                <stop offset="100%">
                    <xsl:attribute name="stop-color">
                        <xsl:value-of select="$var_dsblcolor1"/>
                    </xsl:attribute>                         
                </stop>
            </linearGradient>
            
        </defs>    
    </xsl:template>  
     
    <!--
    
    Генерация тела кнопки
    
    --> 
    
    <xsl:template name="apply_mlib_button_body"> 
        <svg>
            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_mlib_button_class"/>
            <xsl:call-template name="apply_mlib_button_state"/>
            <xsl:call-template name="apply_mlib_button_style"/>          
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
                <xsl:call-template name="apply_mlib_button_class"/>
                <xsl:call-template name="apply_r"/>
            </rect>   
            <xsl:call-template name="apply_mlib_button_caption"/>
            <g>
                <xsl:call-template name="apply_mlib_button_class"/>
                <rect>
                    
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
                    <xsl:call-template name="apply_mlib_button_class"/>
                    <xsl:call-template name="apply_r"/>   
                </rect>
            </g>
        </svg>
    </xsl:template>
 
 
 
    
    <!--
    
    Генерация стиля надписи
    
    -->
    
    <xsl:template name="apply_mlib_button_caption_value_both">
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
    
    <xsl:template name="apply_mlib_button_caption_value_dsbl">
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
    
    <xsl:template name="apply_mlib_button_caption_value_state">
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
    
    <xsl:template name="apply_mlib_button_caption_value"> 
        <xsl:choose>
            <xsl:when test="(boolean(@oncaption) and not(normalize-space(@oncaption)=''))">
                <xsl:choose>
                    <xsl:when test="(boolean(@dsblcaption) and not(normalize-space(@dsblcaption)=''))">                       
                        <xsl:choose>
                            <xsl:when test="(boolean(@state) and not(normalize-space(@state)=''))">
                                <xsl:choose>
                                    <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                                
                                        <xsl:call-template name="apply_mlib_button_caption_value_both"/>                               
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:call-template name="apply_mlib_button_caption_value_state"/>                      
                                    </xsl:otherwise>     
                                </xsl:choose>                                                                                               
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:choose>
                                    <xsl:when test="(boolean(@disable) and not(normalize-space(@disable)=''))">                                
                                        <xsl:call-template name="apply_mlib_button_caption_value_dsbl"/>                                
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
                                <xsl:call-template name="apply_mlib_button_caption_value_state"/>     
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
                                <xsl:call-template name="apply_mlib_button_caption_value_dsbl"/>                                                                                                                                                                           
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
     
     
    <xsl:template name="apply_mlib_button_caption"> 
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
            <xsl:call-template name="apply_mlib_button_class"/>
            <text>
                <xsl:attribute name="x">
                    <xsl:value-of select="(@width - 8) div 2"/>
                </xsl:attribute>
                <xsl:attribute name="y">
                    <xsl:value-of select="(@height - 8) div 2"/>
                </xsl:attribute>     
                <xsl:call-template name="apply_mlib_button_class"/>
                <xsl:call-template name="apply_mlib_button_caption_value"/>
            </text>
        </svg>     
    </xsl:template>
    
    
    
    
    <!--
    
    Основной обработчик
    
    -->
    
    
    <xsl:template match="//mlib:button" name="mlib_button">   
        <g>       
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_mlib_schema"/>   
            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_mlib_button_control"/>            
            <xsl:call-template name="apply_cental_rotate"/>             
            <xsl:call-template name="apply_svg_g_visible"/>                     
            <xsl:call-template  name="apply_mlib_button_body"/>  
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
   
    <xsl:template name="mlib_rect_style">
        <defs>
      
            <xsl:variable name="gradtype">    
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                        <xsl:choose>
                            <xsl:when test="(@gradient-type='tb')">
                                <xsl:text>h</xsl:text>
                            </xsl:when>
                            <xsl:when test="(@gradient-type='c')">
                                <xsl:text>c</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>v</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>                         
                    </xsl:when> 
                    <xsl:otherwise>
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
                    </xsl:otherwise>  
                </xsl:choose>
            </xsl:variable>    
       
            <xsl:choose>
                <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='') and boolean(@color2) and not(normalize-space(@color2)='')">
                    <xsl:choose>
                        <xsl:when test="not($gradtype='c')">                    
                            <linearGradient  x2="100%" y2="100%">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_rect_gradient</xsl:text>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="$gradtype='v'"> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:when>
                                    <xsl:otherwise> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:otherwise>
                                </xsl:choose>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="0.5">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color2"/>                                                         
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                            </linearGradient>
                        </xsl:when>
                        <xsl:otherwise>                            
                            <radialGradient>
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_rect_gradient</xsl:text>
                                </xsl:attribute>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:choose>
                                            <xsl:when test="boolean(@color2) and not(normalize-space(@color2)='')">
                                                <xsl:value-of select="@color2"/>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:value-of select="@color1"/>
                                            </xsl:otherwise> 
                                        </xsl:choose> 
                                    </xsl:attribute>  
                                </stop>
                            </radialGradient>                           
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:when>    
            </xsl:choose>
            
            
            
            <xsl:choose>
                <xsl:when test="boolean(@fillcolor1) and not(normalize-space(@fillcolor1)='') and boolean(@fillcolor2) and not(normalize-space(@fillcolor2)='')">
                    <xsl:choose>
                        <xsl:when test="not($gradtype='c')">                    
                            <linearGradient  x2="100%" y2="100%">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_fillrect_gradient</xsl:text>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="$gradtype='v'"> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:when>
                                    <xsl:otherwise> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:otherwise>
                                </xsl:choose>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="0.5">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor2"/>                                                         
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor1"/>
                                    </xsl:attribute>  
                                </stop>
                            </linearGradient>
                        </xsl:when>
                        <xsl:otherwise>                            
                            <radialGradient>
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_fillrect_gradient</xsl:text>
                                </xsl:attribute>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:choose>
                                            <xsl:when test="boolean(@fillcolor2) and not(normalize-space(@fillcolor2)='')">
                                                <xsl:value-of select="@fillcolor2"/>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:value-of select="@fillcolor1"/>
                                            </xsl:otherwise> 
                                        </xsl:choose> 
                                    </xsl:attribute>  
                                </stop>
                            </radialGradient>                           
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:when>    
            </xsl:choose>                
            
            
            
   
            <style type="text/css">
                
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_gradient_class {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_rect_gradient</xsl:text>
                        <xsl:text>);}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')">
                        <xsl:text>fill : </xsl:text>
                        <xsl:value-of select="@color1"/>
                        <xsl:text>;}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="(@environment='gaz') or (@environment='water') or (@environment='air') or (@environment='oil') or (@environment='stream')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradient</xsl:text>
                        <xsl:value-of select="@environment"/>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>
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
                <xsl:text>#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_fill {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@fillcolor1) and not(normalize-space(@fillcolor1)='')  and boolean(@fillcolor2) and not(normalize-space(@fillcolor2)='')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_fillrect_gradient</xsl:text>
                        <xsl:text>);}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="boolean(@fillcolor1) and not(normalize-space(@fillcolor1)='')">
                        <xsl:text>fill : </xsl:text>
                        <xsl:value-of select="@fillcolor1"/>
                        <xsl:text>;}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="(@fillenvironment='gaz') or (@fillenvironment='water') or (@fillenvironment='air') or (@fillenvironment='oil') or (@fillenvironment='stream')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradient</xsl:text>
                        <xsl:value-of select="@fillenvironment"/>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>
                        <xsl:text>);}
                        </xsl:text>     
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientblack</xsl:text>
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
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">
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
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_gradient_classaccident {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">                
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientaccident</xsl:text>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>                
                        <xsl:text>) !important;</xsl:text> 
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : #FF0000 !important;</xsl:text>                
                    </xsl:otherwise>
                </xsl:choose>                
                <xsl:text>}
                </xsl:text>                

                <xsl:text>
                </xsl:text>    
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_gradient_classalarm {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">                   
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientalarm</xsl:text>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>                
                        <xsl:text>) !important;</xsl:text>
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : #a09020 !important;</xsl:text>                
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:text>}
                </xsl:text>
                
                <xsl:text>
                </xsl:text>    
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_gradient_classnotice {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">                   
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientnotice</xsl:text>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>                
                        <xsl:text>) !important;</xsl:text>
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : #ff0 !important;</xsl:text>                
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:text>}
                </xsl:text>                
        
            </style>  
        </defs>                           
    </xsl:template>  
    
    
    
     <!-- rectclass -->  
     
    <xsl:template name="mlib_rect_rectclass">       
        <xsl:attribute name="class">
            <xsl:choose>
                <xsl:when test="boolean(@param) and not(normalize-space(@param)='')">
                    <xsl:text>#{ (</xsl:text>
                    <xsl:value-of select="@param"/>
                    <xsl:text>).valid  ? '</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_rect_gradient_class</xsl:text>      
                    <xsl:text>' : '</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_rect_gradient_classnone' :default </xsl:text>  
                    <xsl:value-of select="@id"/>
                    <xsl:text>_rect_gradient_classnone }</xsl:text>                     
                </xsl:when>
                <xsl:otherwise> 
                    <xsl:value-of select="@id"/>
                    <xsl:text>_rect_gradient_class</xsl:text>                                   
                </xsl:otherwise>                
            </xsl:choose>      
        </xsl:attribute>
    </xsl:template> 
    
     <!-- rect -->   
    
    <xsl:template name="mlib_rect_rect"> 
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
                
            <xsl:call-template name="mlib_rect_rectclass"/>              
        </rect>          
    </xsl:template>
    
    
   <!-- fillsrectclass -->    
    
    
    <xsl:template name="mlib_fillrect_rectclass">       
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
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classaccident</xsl:text> 
                            </xsl:with-param>
                            <xsl:with-param name="alarm">
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classalarm</xsl:text>                         
                            </xsl:with-param>
                            <xsl:with-param name="notice">
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classnotice</xsl:text>  
                            </xsl:with-param>
                        </xsl:call-template>
                                                   
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:attribute name="class">
                            <xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid  ? '' : '</xsl:text>
                            <xsl:value-of select="@id"/>
                            <xsl:text>_rect_gradient_classnone' :default </xsl:text>  
                            <xsl:value-of select="@id"/>
                            <xsl:text>_rect_gradient_classnone }</xsl:text> 
                        </xsl:attribute> 
                    </xsl:otherwise>                
                </xsl:choose>                                
            </xsl:when>    
        </xsl:choose> 
    </xsl:template>     
    
    
   <!-- fillsrect -->
   
    

    <xsl:template name="mlib_rect_fillrect">    
            
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
                
            <xsl:call-template name="mlib_fillrect_rectclass"/>
               
        </rect>              
            
    </xsl:template>     
   
    
    
    <xsl:template match="//mlib:rect" name="mlib_rect">
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_svg_g_visible"/> 
            
            <xsl:call-template name="mlib_rect_style"/>

            <xsl:call-template name="mlib_rect_rect"/>            
            
            <xsl:call-template name="mlib_rect_fillrect"/> 

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
    
    
    <xsl:template name="mlib_sensor_event">
        <xsl:choose>
            <xsl:when test="not(normalize-space(@param)='')">                  
                <xsl:choose>
                    <xsl:when test="boolean(@sensorevent='valueset')"> 
                        <xsl:attribute name="onclick">
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') </xsl:text> 
                            <xsl:text>mainlib.valueset_click(this, '</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>',</xsl:text>
                            <xsl:value-of select="@width * 1.3"/>
                            <xsl:text>)</xsl:text> 
                        </xsl:attribute>    
                    </xsl:when>
                    <xsl:when test="boolean(@sensorevent='graph')">
                        <xsl:attribute name="onclick">
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') </xsl:text> 
                            <xsl:text>mainlib.graph_click('</xsl:text> 
                            <xsl:value-of select="@param"/>
                            <xsl:text>')</xsl:text>  
                        </xsl:attribute> 
                    </xsl:when>     
                </xsl:choose>                    
            </xsl:when>
        </xsl:choose>         
    </xsl:template>
    
    
 <!-- style -->
    
    
    <xsl:template name="mlib_sensor_style">
        <defs>
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
                <xsl:when test="not(normalize-space(@color1)='') and not(normalize-space(@color2)='')">
                    <xsl:choose>
                        <xsl:when test="not($gradtype='c')">                    
                            <linearGradient  x2="100%" y2="100%">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_sensor_gradient</xsl:text>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="$gradtype='v'"> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:when>
                                    <xsl:otherwise> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:otherwise>
                                </xsl:choose>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="0.5">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color2"/>                                                         
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                            </linearGradient>
                        </xsl:when>
                        <xsl:otherwise>                            
                            <radialGradient>
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_sensor_gradient</xsl:text>
                                </xsl:attribute>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:choose>
                                            <xsl:when test="not(normalize-space(@color2)='')">
                                                <xsl:value-of select="@color2"/>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:value-of select="@color1"/>
                                            </xsl:otherwise> 
                                        </xsl:choose> 
                                    </xsl:attribute>  
                                </stop>
                            </radialGradient>                           
                        </xsl:otherwise>
                    </xsl:choose> 
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
                    <xsl:when test="not(normalize-space(@color1)='')">
                        <xsl:text>fill : </xsl:text>
                        <xsl:value-of select="@color1"/>
                        <xsl:text>;}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="(@environment='gaz') or (@environment='water') or (@environment='air') or (@environment='oil') or (@environment='stream')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradient</xsl:text>
                        <xsl:value-of select="@environment"/>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>
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
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_gradient_classaccident {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">                
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientaccident</xsl:text>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>                
                        <xsl:text>);</xsl:text> 
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : #FF0000;</xsl:text>                
                    </xsl:otherwise>
                </xsl:choose>                
                <xsl:text>}
                </xsl:text>                

                <xsl:text>
                </xsl:text>    
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_gradient_classalarm {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@color1)='')  and not(normalize-space(@color2)='')">                   
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientalarm</xsl:text>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>                
                        <xsl:text>);</xsl:text>
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : #a09020;</xsl:text>                
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:text>}
                </xsl:text>
                
 
                
                <xsl:text>
                </xsl:text>    
                <xsl:text>#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_text {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@alighn) and (@alighn='left')">                    
                        <xsl:text>text-anchor: start;</xsl:text> 
                    </xsl:when>
                    <xsl:when test="boolean(@alighn) and (@alighn='center')">                  
                        <xsl:text>text-anchor: middle;</xsl:text> 
                    </xsl:when>                    
                    <xsl:otherwise> 
                        <xsl:text>text-anchor: end;</xsl:text>    
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:choose>
                    <xsl:when test="not(normalize-space(@fontcolor)='') ">                   
                        <xsl:text>
                        fill : 
                        </xsl:text>
                        <xsl:value-of select="@fontcolor"/>                
                        <xsl:text>;</xsl:text>
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text></xsl:text>                
                    </xsl:otherwise>
                </xsl:choose>  
                <xsl:text>                  
                dominant-baseline: central;  
                -webkit-user-select: none;}
                </xsl:text> 
                
            </style>  
        </defs>                
    </xsl:template>      
    
    
    <!-- fill -->
    
    
    <xsl:template name="mlib_sensor_fill">
        <xsl:choose>         
            <xsl:when test="not(normalize-space(@param)='')">                  
                <xsl:attribute name="class">
                    <xsl:text>#{ (</xsl:text>
                    <xsl:value-of select="@param"/>
                    <xsl:text>).valid  ? '</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_gradient_classon</xsl:text>
                    <xsl:text>' : '</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_gradient_classnone</xsl:text>
                    <xsl:text>' :default </xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_gradient_classnone }</xsl:text>
                </xsl:attribute>                       
            </xsl:when>                      
            <xsl:otherwise>
                <xsl:attribute name="class">
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_gradient_classon</xsl:text>
                </xsl:attribute>    
            </xsl:otherwise> 
        </xsl:choose>         
    </xsl:template> 
      
    
     <!-- rect -->    
    
    <xsl:template name="mlib_sensor_rect">   
        <rect>        
                
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
                
            <xsl:call-template name="mlib_sensor_fill"/>   
            
             <!--xsl:call-template name="mlib_sensor_strokealarm"/-->
        </rect>
    </xsl:template>    
     
    <!-- cursor -->
    
    
    <xsl:template name="mlib_sensor_cursor">
        <xsl:choose>
            <xsl:when test="not(normalize-space(@param)='')">                  
                <xsl:choose>
                    <xsl:when test="((@sensorevent='valueset') or (@sensorevent='graph'))">                  
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
    
    <xsl:template name="mlib_sensor_textcontent">     
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
                        <xsl:text> format(</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text> , '%8.1f') : '</xsl:text>
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
    
    
    <xsl:template name="mlib_sensor_textalarm">

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

    <xsl:template name="mlib_sensor_text">
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
                            
                                
                <xsl:choose>                              
                    <xsl:when test="not(@fontstyle='')">
                        <xsl:attribute name="style">
                            <xsl:value-of select="@fontstyle"/>
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="style">
                            <xsl:text>fill: white; </xsl:text>
                            <xsl:text>fill-size:  </xsl:text>
                            <xsl:value-of select="@height div 1.5"/>
                            <xsl:text>;</xsl:text>
                        </xsl:attribute>                                    
                    </xsl:otherwise>
                </xsl:choose>  
                
                <xsl:attribute name="class">
                    <xsl:value-of select="@id"/>
                    <xsl:text>_sensor_text_class</xsl:text>
                </xsl:attribute>                
                                                   
                <xsl:call-template name="mlib_sensor_textcontent"/>

                <xsl:call-template name="mlib_sensor_textalarm"/>
                
                                                        
            </text>
        </svg>       
    </xsl:template> 
    
    
    <xsl:template name="apply_mlib_sensor_alarmstate">    
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
    
    
    <xsl:template name="apply_mlib_sensor_control_img">    
        <circle  r="3" stroke-width="0">
            <xsl:attribute name="cx">
                <xsl:value-of select="@x +  @width + 3"/> 
            </xsl:attribute> 
            <xsl:attribute name="cy">
                <xsl:value-of select="@y - 3"/>
            </xsl:attribute>         
        </circle>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_sensor_control">    
        <xsl:choose>
            <xsl:when test="not(normalize-space(@control)='')">
                <g>
                    <xsl:attribute name="class">
                        <xsl:text>#{</xsl:text> 
                        <xsl:value-of select="@control"/>
                        <xsl:text> ? 'oncheckcontrol'  : 'offcheckcontrol' :default oncheckcontrol }</xsl:text>
                    </xsl:attribute>                              
                    <xsl:call-template name="apply_mlib_sensor_control_img"/>
                </g>                    
            </xsl:when>
        </xsl:choose>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_sensor_calcbutton">
        <xsl:param name="num"/>
        <xsl:attribute name="onclick">
            <xsl:text>var txtel= document.getElementById('</xsl:text>
            <xsl:value-of select="@id"/>
            <xsl:text>_popup_sensorcalc_sensor_text</xsl:text>  
            <xsl:text>'); if (txtel) { var newtxt= txtel.textContent+'</xsl:text>
            <xsl:value-of select="$num"/>               
            <xsl:text>'; var fltnew = parseFloat(newtxt); if (fltnew==fltnew || newtxt=='-') {txtel.textContent = newtxt;}}</xsl:text>
        </xsl:attribute>
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_sensor_popup"> 
              
        <xsl:choose>
            <xsl:when test="(@sensorevent='valueset') and not(normalize-space(@param)='')">     
                <defs>
                    <svg width="100%" height="100%" viewBox="0 0 128 250"> 
                        <xsl:attribute name="id">
                            <xsl:value-of select="@id"/>
                            <xsl:text>_popup</xsl:text>
                        </xsl:attribute>
                        
                        <xsl:variable name="fontstyle">
                            <xsl:text>fill: yellow; font-size: 18;</xsl:text>                            
                        </xsl:variable>
                           
      
                        <xsl:variable name="popupbody">
                            <sensor x="5" y="7" width="118" height="36" color1="#333"  color2="#555" caption="" r="5" fontcolor="yellow" fontstyle="font-size: 18;" stroke="#eee" stroke-width="1">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_sensorcalc</xsl:text>
                                </xsl:attribute>
                            </sensor> 
                            <button x="5" y="50" width="38" height="38" caption="1" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button1</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">1</xsl:with-param>
                                </xsl:call-template>
                            </button>    
                            <button x="45" y="50" width="38" height="38" caption="2" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button2</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">2</xsl:with-param>
                                </xsl:call-template>                                
                            </button>
                            <button x="85" y="50" width="38" height="38" caption="3" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button3</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">3</xsl:with-param>
                                </xsl:call-template>                                
                            </button>                      
                            <button x="5" y="90" width="38" height="38" caption="4" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button4</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">4</xsl:with-param>
                                </xsl:call-template>                                
                            </button>    
                            <button x="45" y="90" width="38" height="38" caption="5" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button5</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">5</xsl:with-param>
                                </xsl:call-template>                                
                            </button>
                            <button x="85" y="90" width="38" height="38" caption="6" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button6</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">6</xsl:with-param>
                                </xsl:call-template>                                
                            </button> 
                            <button x="5" y="130" width="38" height="38" caption="7" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button7</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">7</xsl:with-param>
                                </xsl:call-template>                                
                            </button>    
                            <button x="45" y="130" width="38" height="38" caption="8" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button8</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">8</xsl:with-param>
                                </xsl:call-template>                                
                            </button>
                            <button x="85" y="130" width="38" height="38" caption="9" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_button9</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">9</xsl:with-param>
                                </xsl:call-template>                                
                            </button>    
                            <button x="5" y="170" width="38" height="38" caption="." r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttondot</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">.</xsl:with-param>
                                </xsl:call-template>
                            </button>    
                            <button x="45" y="170" width="38" height="38" caption="0" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonn</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">0</xsl:with-param>
                                </xsl:call-template>
                            </button>
                            <button x="85" y="170" width="38" height="38" caption="C" r="5" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonc</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="onclick">
                                    <xsl:text>var txtel= document.getElementById('</xsl:text>
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_sensorcalc_sensor_text</xsl:text>  
                                    <xsl:text>'); if (txtel) {if (txtel.textContent.length>0) {txtel.textContent=txtel.textContent.substring(0, txtel.textContent.length-1);}}</xsl:text>
                                </xsl:attribute>
                            </button>     
                            <button x="5" y="210" width="38" height="38" caption="-" r="5"  fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonnegativ</xsl:text>
                                </xsl:attribute>
                                <xsl:call-template name="apply_mlib_sensor_calcbutton">
                                    <xsl:with-param name="num">-</xsl:with-param>
                                </xsl:call-template>
                            </button>    
                            <button x="45" y="210" width="38" height="38" caption="x"  r="5" color1="#800" color2="#B00" fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttond</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="onclick">
                                    <xsl:text>var popuptmp= document.getElementById('</xsl:text>
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_body');  if (popuptmp) {if (popuptmp.clearpopup) {popuptmp.clearpopup();}}</xsl:text>
                                </xsl:attribute>                                
                            </button>
                            <button x="85" y="210" width="38" height="38" caption="ok"  r="5" color1="#080" color2="#0B0"  fontstyle="{$fontstyle}">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_buttonok</xsl:text>
                                </xsl:attribute>
                                <xsl:attribute name="onclick">
                                    <xsl:text>var txtel= document.getElementById('</xsl:text> 
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_sensorcalc_sensor_text</xsl:text>  
                                    <xsl:text>'); if (txtel) { if (txtel.textContent.length>0) { $$(('</xsl:text>
                                    <xsl:value-of select="@param"/> 
                                    <xsl:text> @= ' + txtel.textContent));}}</xsl:text> 
                                    <xsl:text>var popuptmp= document.getElementById('</xsl:text>
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_popup_body');  if (popuptmp) {if (popuptmp.clearpopup) {popuptmp.clearpopup();}}</xsl:text>
                                </xsl:attribute>                                
                            </button>                     
                        </xsl:variable>
                
                        <xsl:for-each select="exsl:node-set($popupbody)/*">
                            <xsl:choose>
                                <xsl:when test="local-name()='button'">
                                    <xsl:call-template name="mlib_button"/>
                                </xsl:when>
                                <xsl:when test="local-name()='rect'">
                                    <xsl:call-template name="mlib_button"/>
                                </xsl:when> 
                                <xsl:when test="local-name()='sensor'">
                                    <xsl:call-template name="mlib_sensor"/>
                                </xsl:when>                         
                            </xsl:choose>
                        </xsl:for-each>  
                
                
                    </svg>
                </defs>  
            </xsl:when>
        </xsl:choose>
    </xsl:template>
        
  
    
    <xsl:template match="//mlib:sensor" name="mlib_sensor">
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_svg_g_visible"/> 
            
            <xsl:call-template name="mlib_sensor_event"/> 
            
            <xsl:call-template name="mlib_sensor_cursor"/>
            
            <xsl:call-template name="mlib_sensor_style"/>
            
            <xsl:call-template name="mlib_sensor_rect"/> 
            
            <xsl:call-template name="mlib_sensor_text"/>
            
            <xsl:call-template name="apply_mlib_sensor_alarmstate"/> 
            
            <xsl:call-template name="apply_mlib_sensor_control"/>
            
            <xsl:call-template name="apply_mlib_sensor_popup"/>
                       
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
    
    
    <xsl:template name="apply_mlib_path_main">
        <path fill="none">
   
            <xsl:attribute name="d">
                <xsl:choose>                              
                    <xsl:when test="not(@d='')">  
                        <xsl:value-of select="@d"/>
                    </xsl:when>   
                    <xsl:otherwise> </xsl:otherwise>
                </xsl:choose>    
            </xsl:attribute>
            
            <xsl:choose>                              
                <xsl:when test="not(@filter='')">
                    <xsl:attribute name="filter">
                        <xsl:text>url(#filter_lib3)</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose>
            
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
            
            <xsl:attribute name="stroke">
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
            </xsl:attribute>
                       
        </path>        
        
    </xsl:template>
    
    
    <xsl:template name="apply_mlib_path_fill">
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

            
                    <xsl:attribute name="stroke">
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
                    </xsl:attribute>
         
                </path>
            </xsl:when>        
        </xsl:choose>               
    </xsl:template>
    
    
    <xsl:template match="//mlib:path" >
        <g>    
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_mlib_schema"/>
            <xsl:call-template name="apply_svg_g_visible"/> 

            <xsl:call-template name="apply_mlib_path_main"/>
            
            <xsl:call-template name="apply_mlib_path_fill"/>
            
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
    
    
    <xsl:template match="//mlib:alarmtable" >
         
        <foreignObject>

            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_mlib_schema"/>
            
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
                          font-family: sans-serif;
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
                          font-size: larger;
                          text-shadow: black 1px 1px 0px, #aaa  0 0 1em;
                          color: white;
                          background:  -webkit-linear-gradient(#333 0%, #111 50%, #333 100%);}
                            
                        td{
                          display: table-cell;
                          border: 1px;                         
                          padding: 3px;
                          border: 1px solid #999999;
                          background:   -webkit-linear-gradient(#eee 0%, #ddd 50%, #eee 100%);}


                        tr.avaron{
                          color: red;
                          font-weight: bold;}

                        tr.alarmon{
                          color: orange;
                          font-weight: bold;}

                        tr.noticeon{
                          color: darksalmon;
                          font-weight: bold;}

                        tr.avarkvit{
                          color:  dimgray;
                          font-weight: normal;}

                        tr.alarmkvit{
                          color:  darkgrey;
                          font-weight: normal;}

                        tr.noticekvit{
                          color:  lightsteelblue;
                          font-weight: normal;} 
                          
                    </style>    
                </head>

                <body xmlns="http://www.w3.org/1999/xhtml">
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
                            <script type="text/javascript">                           
                                <xsl:text>var testsalarm=new libutil.alarmtable(this.document.getElementById('</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>'));</xsl:text>
                            </script>
                            <tbody xmlns="http://www.w3.org/1999/xhtml">       
                                <tr> 
                                    <xsl:attribute name="style">                    
                                        <xsl:value-of select="$rectvarw"/>
                                    </xsl:attribute>  
                                    <th >Время</th>
                                    <th >Тэг</th>
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
    
    
    <xsl:template name="mlib_translate"> 
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
                    <xsl:call-template name="mlib_rotate"/>
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
                    <xsl:call-template name="mlib_rotate"/>
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
                    <xsl:call-template name="mlib_rotate"/>
                </g>
            </xsl:when>            
            <xsl:otherwise>
                <xsl:call-template name="mlib_rotate"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    

    <xsl:template name="mlib_rotate"> 
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
                            <xsl:call-template name="mlib_scale"/>
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
                            <xsl:call-template name="mlib_scale"/>
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
                            <xsl:call-template name="mlib_scale"/>
                        </g>
                    </xsl:when>            
                    <xsl:otherwise>
                        <xsl:call-template name="mlib_scale"/>
                    </xsl:otherwise>
                </xsl:choose>                
             

            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="mlib_scale"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template> 
    
    
    <xsl:template name="mlib_scale"> 
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
    
    
    <xsl:template match="//mlib:group">
        <svg>
            <xsl:attribute name="isgoupelement">
                <xsl:text>true</xsl:text>
            </xsl:attribute>
            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_mlib_schema"/>
            <xsl:call-template name="apply_lib_mouseevent"/> 
            
            <g>
                <xsl:call-template name="apply_svg_g_visible_binding"/>          
                <rect stroke="white" fill="white" opacity="0.0">
                    <xsl:call-template name="apply_0_0_width_height"/> 
                </rect>
                <g> 
                    <xsl:call-template name="mlib_translate"/>
                </g>
            </g>
        </svg>
    </xsl:template>    
    
    
   <!--
   
   
   slider
   
   
   -->
   
   
   <!-- style   -->
   
    <xsl:template name="apply_mlib_slider_style">
        <defs>
      
            <xsl:variable name="gradtype">    
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">
                        <xsl:choose>
                            <xsl:when test="(@gradient-type='tb')">
                                <xsl:text>h</xsl:text>
                            </xsl:when>
                            <xsl:when test="(@gradient-type='c')">
                                <xsl:text>c</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>v</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>                         
                    </xsl:when> 
                    <xsl:otherwise>
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
                    </xsl:otherwise>  
                </xsl:choose>
            </xsl:variable>    
       
            <xsl:choose>
                <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='') and boolean(@color2) and not(normalize-space(@color2)='')">
                    <xsl:choose>
                        <xsl:when test="not($gradtype='c')">                    
                            <linearGradient  x2="100%" y2="100%">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_slider_gradient</xsl:text>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="$gradtype='v'"> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:when>
                                    <xsl:otherwise> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:otherwise>
                                </xsl:choose>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="0.5">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color2"/>                                                         
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                            </linearGradient>
                        </xsl:when>
                        <xsl:otherwise>                            
                            <radialGradient>
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_slider_gradient</xsl:text>
                                </xsl:attribute>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@color1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:choose>
                                            <xsl:when test="boolean(@color2) and not(normalize-space(@color2)='')">
                                                <xsl:value-of select="@color2"/>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:value-of select="@color1"/>
                                            </xsl:otherwise> 
                                        </xsl:choose> 
                                    </xsl:attribute>  
                                </stop>
                            </radialGradient>                           
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:when>    
            </xsl:choose>
            
            
            
            <xsl:choose>
                <xsl:when test="boolean(@fillcolor1) and not(normalize-space(@fillcolor1)='') and boolean(@fillcolor2) and not(normalize-space(@fillcolor2)='')">
                    <xsl:choose>
                        <xsl:when test="not($gradtype='c')">                    
                            <linearGradient  x2="100%" y2="100%">
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_fillrect_gradient</xsl:text>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="$gradtype='v'"> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:when>
                                    <xsl:otherwise> 
                                        <xsl:attribute name="x1">
                                            <xsl:text>100%</xsl:text>
                                        </xsl:attribute>
                                        <xsl:attribute name="y1">
                                            <xsl:text>0%</xsl:text>
                                        </xsl:attribute>
                                    </xsl:otherwise>
                                </xsl:choose>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="0.5">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor2"/>                                                         
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor1"/>
                                    </xsl:attribute>  
                                </stop>
                            </linearGradient>
                        </xsl:when>
                        <xsl:otherwise>                            
                            <radialGradient>
                                <xsl:attribute name="id">
                                    <xsl:value-of select="@id"/>
                                    <xsl:text>_fillslider_gradient</xsl:text>
                                </xsl:attribute>                               
                                <stop  offset="0">
                                    <xsl:attribute name="stop-color">
                                        <xsl:value-of select="@fillcolor1"/>
                                    </xsl:attribute>  
                                </stop>
                                <stop  offset="1">
                                    <xsl:attribute name="stop-color">
                                        <xsl:choose>
                                            <xsl:when test="boolean(@fillcolor2) and not(normalize-space(@fillcolor2)='')">
                                                <xsl:value-of select="@fillcolor2"/>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:value-of select="@fillcolor1"/>
                                            </xsl:otherwise> 
                                        </xsl:choose> 
                                    </xsl:attribute>  
                                </stop>
                            </radialGradient>                           
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:when>    
            </xsl:choose>                
            
            
            
   
            <style type="text/css">
                
                
                <xsl:text>
                </xsl:text>
                <xsl:text>#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sliderbutton[captured="captured"] {         
                            opacity: 0;}
                </xsl:text>  
                
                <xsl:text>
                </xsl:text>
                <xsl:text>.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_slider_gradient_class {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient</xsl:text>
                        <xsl:text>);}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')">
                        <xsl:text>fill : </xsl:text>
                        <xsl:value-of select="@color1"/>
                        <xsl:text>;}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="(@environment='gaz') or (@environment='water') or (@environment='air') or (@environment='oil') or (@environment='stream')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradient</xsl:text>
                        <xsl:value-of select="@environment"/>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>
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
                <xsl:text>#</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_slider_fill {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@fillcolor1) and not(normalize-space(@fillcolor1)='')  and boolean(@fillcolor2) and not(normalize-space(@fillcolor2)='')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_fillslider_gradient</xsl:text>
                        <xsl:text>);}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="boolean(@fillcolor1) and not(normalize-space(@fillcolor1)='')">
                        <xsl:text>fill : </xsl:text>
                        <xsl:value-of select="@fillcolor1"/>
                        <xsl:text>;}
                        </xsl:text>        
                    </xsl:when>
                    <xsl:when test="(@fillenvironment='gaz') or (@fillenvironment='water') or (@fillenvironment='air') or (@fillenvironment='oil') or (@fillenvironment='stream')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradient</xsl:text>
                        <xsl:value-of select="@fillenvironment"/>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>
                        <xsl:text>);}
                        </xsl:text>     
                    </xsl:when>
                    <xsl:otherwise> 
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:text>gradientblack</xsl:text>
                        <xsl:text>_</xsl:text>
                        <xsl:value-of select="$gradtype"/>
                        <xsl:text>);}
                        </xsl:text> 
                    </xsl:otherwise>                    
                </xsl:choose>    
    
                <xsl:text>
                </xsl:text>    
                <xsl:text>.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_slider_gradient_classnone {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">
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
    </xsl:template>  
  
   
    <xsl:template name="apply_mlib_slider_stroke">
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
    
    <xsl:template name="apply_mlib_slider_strokewidth">
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
    
    
    <xsl:template name="apply_mlib_slider_sliderrectclass"> 
        <xsl:attribute name="class">
            <xsl:choose> 
                <xsl:when test="not(normalize-space(@param)='')">  
                    <xsl:text>#{ </xsl:text>
                    <xsl:text>(</xsl:text>
                    <xsl:value-of select="@param"/>
                    <xsl:text>).valid ? '</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_slider_gradient_class' : '</xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_slider_gradient_classnone' :default </xsl:text>
                    <xsl:value-of select="@id"/>
                    <xsl:text>_slider_gradient_classnone }</xsl:text>            
                </xsl:when>
                <xsl:otherwise>
                    <xsl:attribute name="class">
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient_class</xsl:text>
                    </xsl:attribute>                      
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>       
    </xsl:template>      
    
    
    <xsl:template name="apply_mlib_slider_sliderrect"> 
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
            
            <xsl:call-template name="apply_mlib_slider_sliderrectclass"/>
            
            <xsl:call-template name="apply_mlib_slider_stroke"/>
            <xsl:call-template name="apply_mlib_slider_strokewidth"/>
    
        </rect>
    </xsl:template>
    
    <xsl:template name="apply_mlib_slider_sliderfillrect"> 
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
            
            <xsl:attribute name="class">
                <xsl:choose> 
                    <xsl:when test="(boolean(@param) and not(normalize-space(@param)=''))">  
                        <xsl:text>#{ </xsl:text>
                        <xsl:text>(</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>).valid ? '</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient_class' : '</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient_classnone' :default </xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_slider_gradient_classnone }</xsl:text>            
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="class">
                            <xsl:value-of select="@id"/>
                            <xsl:text>_slider_gradient_class</xsl:text>
                        </xsl:attribute>                      
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:attribute>
            
            <xsl:call-template name="apply_lib_fillrectangle"> 
                <xsl:with-param name="param" select=" @param"/>
                <xsl:with-param name="x" select=" @width * (1 - $kw) div 2"/>
                <xsl:with-param name="y" select="@height  * (1 - $kh) div 2"/>
                <xsl:with-param name="width" select="@width *  $kw"/>
                <xsl:with-param name="height" select="@height * $kh"/>
                <xsl:with-param name="direction" select=" @direction"/>
                <xsl:with-param name="stroke-width" select="@stroke-width"/>
            </xsl:call-template>
                       
            <xsl:call-template name="apply_mlib_slider_strokewidth"/>
            
            <xsl:call-template name="apply_r"/>
    
        </rect>
    </xsl:template> 
    

   
    
    <xsl:template name="apply_mlib_slider_button"> 
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
                            <xsl:when test="not(normalize-space(@slidercolor1)='')"><xsl:value-of select="@slidercolor1"/></xsl:when>
                            <xsl:otherwise>green</xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>
                </circle> 
                <circle cx="{$size div 2}" cy="{$size div 2}" r="{$size div 3}" stroke="{@stroke}" stroke-width="0">
                    <xsl:attribute name="fill">
                        <xsl:choose>
                            <xsl:when test="not(normalize-space(@slidercolor2)='')"><xsl:value-of select="@slidercolor2"/></xsl:when>
                            <xsl:otherwise>red</xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>
                </circle>                 
            </symbol>
        </defs>    
    </xsl:template>    
    
    
    <xsl:template name="apply_mlib_slider_buttoncontrol"> 
    
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
        
        <xsl:call-template name="apply_mlib_slider_button">
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
                <xsl:text>if (this.getAttribute('cursor')=='pointer') {this.setAttribute('captured','captured');mainlib.create_shadow_slider(this,</xsl:text>
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
                <xsl:text>if (this.hasAttribute('captured'))  this.removeAttribute('captured')</xsl:text>            
            </xsl:attribute> 
            
            <xsl:call-template name="mlib_slider_cursor"/>
            
            <xsl:call-template name="apply_mlib_slider_stroke"/>
            
            <xsl:call-template name="apply_mlib_slider_strokewidth"/> 
            
        </use>    
    </xsl:template>  
    
    <xsl:template name="mlib_slider_cursor">
        <xsl:choose>
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
   
   
    <xsl:template match="//mlib:slider">
        <svg>        
            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_mlib_schema"/>
            <xsl:call-template name="apply_svg_g_visible_binding"/>           
            <xsl:call-template name="apply_mlib_slider_style"/>
            <g>           
                <rect stroke="white" fill="white" opacity="0.0">
                    <xsl:call-template name="apply_0_0_width_height"/> 
                </rect>
                
                <xsl:call-template name="apply_mlib_slider_sliderrect"/>
                
                <xsl:call-template name="apply_mlib_slider_sliderfillrect"/>
                
                <xsl:call-template name="apply_mlib_slider_buttoncontrol"/> 
            </g>
        </svg>
    </xsl:template>   
    
    
</xsl:stylesheet>
