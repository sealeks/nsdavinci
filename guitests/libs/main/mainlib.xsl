<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:mlib="http://dvnci/mlib"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
extension-element-prefixes="mlib">
    
    

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
                    <xsl:attribute name="class">
                        <xsl:text>#{ (alarmlevel(</xsl:text>
                        <xsl:value-of select="@alarms"/>
                        <xsl:text>)==3) ? 'accident' : (</xsl:text>
                        <xsl:text>( alarmlevel(</xsl:text>
                        <xsl:value-of select="@alarms"/> 
                        <xsl:text>)==2) ? 'alarm' : </xsl:text>
                        <xsl:text>  'notice')  :default accident }</xsl:text>
                    </xsl:attribute>                 
                    <circle cx="500" cy="500" r="500"/>
                    <animate  attributeType="XML" attributeName="opacity"  dur="500ms" calcMode = "linear" repeatCount="indefinite">
                        <xsl:attribute name="values">
                            <xsl:text>#{ ack(</xsl:text>
                            <xsl:value-of select="@alarms"/>
                            <xsl:text>) ? '1;1' : </xsl:text>
                            <xsl:text>( nack(</xsl:text>
                            <xsl:value-of select="@alarms"/> 
                            <xsl:text>) ? '0;1' : </xsl:text>
                            <xsl:text>  '0;0')  :default 0;0 }</xsl:text>
                        </xsl:attribute> 
                    </animate>                      
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
                <xsl:choose>             
                    <xsl:when test="boolean(@rauto) and not(normalize-space(@rauto)='')">   
                        <xsl:attribute name="onclick">
                            <!--xsl:call-template name="startcddata"/-->
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                            <xsl:text>mainlib.armatura_auto_popup(this, '</xsl:text>
                            <xsl:value-of select="@header"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="$armaturakind"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@auto"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@ron"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@roff"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@rauto"/>                           
                            <xsl:text>'</xsl:text>                           
                            <xsl:text>);};</xsl:text>
                            <!--xsl:call-template name="stopcddata"/-->
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="onclick">
                            <!--xsl:call-template name="startcddata"/-->
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                            <xsl:text>mainlib.armatura_popup(this, '</xsl:text>
                            <xsl:value-of select="@header"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="$armaturakind"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@ron"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@roff"/>                           
                            <xsl:text>'</xsl:text>                           
                            <xsl:text>);};</xsl:text>
                            <!--xsl:call-template name="stopcddata"/-->
                        </xsl:attribute>  
                    </xsl:otherwise>                            
                </xsl:choose>
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
  
  
        <!--
    
    Основной обработчик
    
    -->
      
    
    <xsl:template match="//mlib:armatura" >   
        <g>       
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
                       
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <!--xsl:call-template  name="apply_visible"/-->
            
            <xsl:call-template name="apply_svg_g_visible"/> 
                                                                   
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
            
            <xsl:call-template name="apply_mlib_aratura_cursor"/>
                       
            <xsl:call-template name="apply_mlib_aratura_event"/>
            
            <xsl:call-template name="apply_mlib_aratura_style"/>
            

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
                    <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
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
                            <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
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
    
    
    <xsl:template match="//mlib:button" >   
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
            <xsl:when test="boolean(@param) and not(normalize-space(@param)='')">            
                <xsl:choose>
                    <xsl:when test="boolean(@alarms) and not(normalize-space(@alarms)='')"> 
                    
                        <animate  attributeType="XML" attributeName="class"  dur="500ms" calcMode = "discrete" repeatCount="indefinite">
                            <xsl:attribute name="values">                   
                                <xsl:text>#{ ack(</xsl:text>
                                <xsl:value-of select="@alarms"/>
                                <xsl:text>) ? ( (alarmlevel(</xsl:text>
                                <xsl:value-of select="@alarms"/>
                                <xsl:text>)==1) ? '</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classnotice</xsl:text>
                                <xsl:text>;</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classnotice</xsl:text>
                                <xsl:text>'  : ((alarmlevel(</xsl:text>
                                <xsl:value-of select="@alarms"/>
                                <xsl:text>)==2) ? '</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classalarm</xsl:text>
                                <xsl:text>;</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classalarm</xsl:text>
                                <xsl:text>' : '</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classaccident</xsl:text>
                                <xsl:text>;</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classaccident</xsl:text>
                                <xsl:text>')) : </xsl:text>
                                <xsl:text>( nack(</xsl:text>
                                <xsl:value-of select="@alarms"/>
                                <xsl:text>) ? ( (alarmlevel(</xsl:text>
                                <xsl:value-of select="@alarms"/>
                                <xsl:text>)==1) ? '</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classnotice</xsl:text>
                                <xsl:text>; '  : ((alarmlevel(</xsl:text>
                                <xsl:value-of select="@alarms"/>
                                <xsl:text>)==2) ? '</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classalarm</xsl:text>
                                <xsl:text>; ' : '</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>_rect_gradient_classaccident</xsl:text>                                
                                <xsl:text>; ')) : ' ; ') :default }</xsl:text>
                            </xsl:attribute> 
                        </animate>                                  
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
        <xsl:variable name="landsc">
            <xsl:choose>
                <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">v</xsl:when> 
                <xsl:otherwise>h</xsl:otherwise>  
            </xsl:choose>
        </xsl:variable>
            
        <rect >
            
            <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
                <xsl:text>_rect_fill</xsl:text>
            </xsl:attribute> 
             
            <xsl:choose>
                <xsl:when test="boolean(@direction='bt') or boolean(@direction='rl')">      
                    <xsl:attribute name="transform">
                        <xsl:text>translate(</xsl:text>
                        <xsl:value-of select="@width"/>
                        <xsl:text>,</xsl:text>
                        <xsl:value-of select="@height"/>
                        <xsl:text>)</xsl:text>
                        <xsl:text> rotate(</xsl:text>
                        <xsl:text>180,</xsl:text>
                        <xsl:value-of select="@x"/>
                        <xsl:text> , </xsl:text>
                        <xsl:value-of select="@y"/>
                        <xsl:text>)</xsl:text>
                    </xsl:attribute>  
                </xsl:when> 
            </xsl:choose>            
                
            <xsl:attribute name="x">
                <xsl:value-of select="@x"/>
            </xsl:attribute>
            <xsl:attribute name="y">
                <xsl:value-of select="@y"/>
            </xsl:attribute>
                
             
            <xsl:choose>
                <xsl:when test="$landsc='h'">
                    <xsl:attribute name="width">
                        <xsl:text>#{ (</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text> - </xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>.mineu)/</xsl:text>
                        <xsl:text>(</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>.maxeu - </xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>.mineu) *</xsl:text>
                        <xsl:value-of select="@width"/>
                        <xsl:text>}</xsl:text>
                    </xsl:attribute>
                    <xsl:attribute name="height">
                        <xsl:value-of select="@height"/>
                    </xsl:attribute>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:attribute name="height">
                        <xsl:text>#{ (</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text> - </xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>.mineu)/</xsl:text>
                        <xsl:text>(</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>.maxeu - </xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>.mineu) *</xsl:text>
                        <xsl:value-of select="@height"/>
                        <xsl:text>}</xsl:text>
                    </xsl:attribute>
                    <xsl:attribute name="width">
                        <xsl:value-of select="@width"/>
                    </xsl:attribute>
                </xsl:otherwise>                    
            </xsl:choose> 
                
                <!-- Direction-->
                
            <xsl:choose>
                <xsl:when test="boolean(@stroke-width)">
                    <xsl:attribute name="stroke-width">
                        <xsl:value-of select="@stroke-width"/>
                    </xsl:attribute>
                    <xsl:attribute name="stroke">
                        <xsl:text>trasparent</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose> 
                
            <xsl:call-template name="apply_r"/>
                
            <xsl:call-template name="mlib_fillrect_rectclass"/>
               
        </rect>              
            
    </xsl:template>     
   
    
    
    <xsl:template match="//mlib:rect" >
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
            <xsl:when test="boolean(@param) and not(normalize-space(@param)='')">                  
                <xsl:choose>
                    <xsl:when test="boolean(@sensorevent) and (@sensorevent='valueset')"> 
                        <xsl:attribute name="onclick">
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') </xsl:text> 
                            <xsl:text>mainlib.valueset_click(this, '</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>',</xsl:text>
                            <xsl:value-of select="@width * 1.3"/>
                            <xsl:text>)</xsl:text> 
                        </xsl:attribute>    
                    </xsl:when>
                    <xsl:when test="boolean(@sensorevent) and (@sensorevent='graph')">
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
                <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='') and boolean(@color2) and not(normalize-space(@color2)='')">
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
            
            <style type="text/css">
                
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_gradient_classon {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">
                        <xsl:text>fill : url(#</xsl:text>
                        <xsl:value-of select="@id"/>
                        <xsl:text>_sensor_gradient</xsl:text>
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
                <xsl:text>rect.</xsl:text>
                <xsl:value-of select="@id"/>
                <xsl:text>_sensor_gradient_classnone {
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
                <xsl:text>_sensor_gradient_classaccident {
                </xsl:text>
                <xsl:choose>
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">                
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
                    <xsl:when test="boolean(@color1) and not(normalize-space(@color1)='')  and boolean(@color2) and not(normalize-space(@color2)='')">                   
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
                    <xsl:when test="boolean(@fontcolor) and not(normalize-space(@fontcolor)='') ">                   
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
            <xsl:when test="boolean(@param) and not(normalize-space(@param)='')">                  
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
            <xsl:when test="boolean(@param) and not(normalize-space(@param)='')">                  
                <xsl:choose>
                    <xsl:when test="boolean(@sensorevent) and ((@sensorevent='valueset') or (@sensorevent='graph'))">                  
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
            <xsl:when test="boolean(@param) and not(normalize-space(@param)='')">
                
                <xsl:variable name="textdefault">
                    <xsl:choose>                              
                        <xsl:when test="boolean(@caption) and not(normalize-space(@caption)='')">
                            <xsl:value-of select="@caption"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>?</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:variable>
                
                <xsl:choose>                                      
                    <xsl:when test="boolean(@format) and not(normalize-space(@format)='')">
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
                    <xsl:when test="boolean(@caption) and not(normalize-space(@caption)='')">
                        <xsl:value-of select="@caption"/>
                    </xsl:when>
                </xsl:choose> 
            </xsl:otherwise>
        </xsl:choose> 
    </xsl:template>
    
    <!-- textalarm -->
    
    
    <xsl:template name="mlib_sensor_textalarm">

        <xsl:choose>
            <xsl:when test="(boolean(@alarms-low) and not(normalize-space(@alarms-low)='')) or( boolean(@alarms-high) and not(normalize-space(@alarms-high)=''))">
                
                <xsl:variable name="alarmlist">
                    <xsl:choose>
                        <xsl:when test="boolean(@alarms-low) and not(normalize-space(@alarms-low)='') and boolean(@alarms-high) and not(normalize-space(@alarms-high)='')  and boolean(@alarms) and not(normalize-space(@alarms)='')  ">                    
                            <xsl:value-of select="@alarms-low"/> 
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@alarms-high"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@alarms"/>                           
                        </xsl:when>
                        <xsl:when test="boolean(@alarms-low) and not(normalize-space(@alarms-low)='') and boolean(@alarms-high) and not(normalize-space(@alarms-high)='')">                    
                            <xsl:value-of select="@alarms-low"/> 
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@alarms-high"/>                  
                        </xsl:when> 
                        <xsl:when test="boolean(@alarms-low) and not(normalize-space(@alarms-low)='')  and boolean(@alarms) and not(normalize-space(@alarms)='')  ">                    
                            <xsl:value-of select="@alarms-low"/> 
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@alarms"/>                           
                        </xsl:when>   
                        <xsl:when test=" boolean(@alarms-high) and not(normalize-space(@alarms-high)='')  and boolean(@alarms) and not(normalize-space(@alarms)='')  ">                    
                            <xsl:value-of select="@alarms-high"/>
                            <xsl:text>,</xsl:text>
                            <xsl:value-of select="@alarms"/>                           
                        </xsl:when>                        
                        <xsl:when test="boolean(@alarms-low) and not(normalize-space(@alarms-low)='')  ">                    
                            <xsl:value-of select="@alarms-low"/>                           
                        </xsl:when>
                        <xsl:when test="boolean(@alarms-high) and not(normalize-space(@alarms-high)='')  ">                    
                            <xsl:value-of select="@alarms-high"/>                           
                        </xsl:when> 
                        <xsl:when test="boolean(@alarms) and not(normalize-space(@alarms)='')  ">                    
                            <xsl:value-of select="@alarms"/>                           
                        </xsl:when>                          
                        <xsl:otherwise> 
                            <xsl:text></xsl:text>    
                        </xsl:otherwise>
                    </xsl:choose>                   
                </xsl:variable> 
                               
                <animate  attributeType="XML" attributeName="class"  dur="500ms" calcMode = "discrete" repeatCount="indefinite">
                    <xsl:attribute name="values">
                        <xsl:text>#{ ack(</xsl:text>
                        <xsl:value-of select="$alarmlist"/>
                        <xsl:text>) ? ( (alarmlevel(</xsl:text>
                        <xsl:value-of select="$alarmlist"/>
                        <xsl:text>)==1) ? 'notice;notice'  : ((alarmlevel(</xsl:text>
                        <xsl:value-of select="$alarmlist"/>
                        <xsl:text>)==2) ? 'alarm;alarm' : 'accident;accident')) : </xsl:text>
                        <xsl:text>( nack(</xsl:text>
                        <xsl:value-of select="$alarmlist"/>
                        <xsl:text>) ? ( (alarmlevel(</xsl:text>
                        <xsl:value-of select="$alarmlist"/>
                        <xsl:text>)==1) ? 'notice; '  : ((alarmlevel(</xsl:text>
                        <xsl:value-of select="$alarmlist"/>
                        <xsl:text>)==2) ? 'alarm; ' : 'accident; ')) : ' ') :default }</xsl:text>
                    </xsl:attribute> 
                </animate>  
                
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
                    <xsl:when test="boolean(@fontstyle) and not(@fontstyle='')">
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
            <xsl:when test="(boolean(@alarms-low) and not(normalize-space(@alarms-low)=''))">
                <g  class="accident">  
                    <polygon>
                        <xsl:attribute name="class">
                            <xsl:text>#{ (alarmlevel(</xsl:text>
                            <xsl:value-of select="@alarms-low"/>
                            <xsl:text>)==3) ? 'accident' : (</xsl:text>
                            <xsl:text>( alarmlevel(</xsl:text>
                            <xsl:value-of select="@alarms-low"/> 
                            <xsl:text>)==2) ? 'alarm' : </xsl:text>
                            <xsl:text>  'notice')  :default accident }</xsl:text>
                        </xsl:attribute>                         
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
                        <animate  attributeType="XML" attributeName="opacity"  dur="500ms" calcMode = "linear" repeatCount="indefinite">
                            <xsl:attribute name="values">
                                <xsl:text>#{ ack(</xsl:text>
                                <xsl:value-of select="@alarms-low"/>
                                <xsl:text>) ? '1;1' : </xsl:text>
                                <xsl:text>( nack(</xsl:text>
                                <xsl:value-of select="@alarms-low"/> 
                                <xsl:text>) ? '0;1' : </xsl:text>
                                <xsl:text>  '0;0')  :default 0;0 }</xsl:text>
                            </xsl:attribute> 
                        </animate>
                    </polygon>
                </g>     
            </xsl:when>   
        </xsl:choose>  
        <xsl:choose>                
            <xsl:when test="(boolean(@alarms-high) and not(normalize-space(@alarms-high)=''))">
                <g  class="accident">                 
                    <polygon>    
                        <xsl:attribute name="class">
                            <xsl:text>#{ (alarmlevel(</xsl:text>
                            <xsl:value-of select="@alarms-high"/>
                            <xsl:text>)==3) ? 'accident' : (</xsl:text>
                            <xsl:text>( alarmlevel(</xsl:text>
                            <xsl:value-of select="@alarms-high"/> 
                            <xsl:text>)==2) ? 'alarm' : </xsl:text>
                            <xsl:text>  'notice')  :default accident }</xsl:text>
                        </xsl:attribute> 
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
                    
                        <animate  attributeType="XML" attributeName="opacity"  dur="500ms" calcMode = "linear" repeatCount="indefinite">
                            <xsl:attribute name="values">
                                <xsl:text>#{ ack(</xsl:text>
                                <xsl:value-of select="@alarms-high"/>
                                <xsl:text>) ? '1;1' : </xsl:text>
                                <xsl:text>( nack(</xsl:text>
                                <xsl:value-of select="@alarms-high"/> 
                                <xsl:text>) ? '0;1' : </xsl:text>
                                <xsl:text>  '0;0')  :default 0;0 }</xsl:text>
                            </xsl:attribute> 
                        </animate>
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
            <xsl:when test="boolean(@control) and not(normalize-space(@control)='')">
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
        
  
    
    <xsl:template match="//mlib:sensor" >
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
                    <xsl:when test="boolean(@d) and not(@d='')">  
                        <xsl:value-of select="@d"/>
                    </xsl:when>   
                    <xsl:otherwise> </xsl:otherwise>
                </xsl:choose>    
            </xsl:attribute>
            
            <xsl:choose>                              
                <xsl:when test="boolean(@filter) and not(@filter='')">
                    <xsl:attribute name="filter">
                        <xsl:text>url(#filter_lib3)</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose>
            
            <xsl:attribute name="stroke-width">
                <xsl:choose>
                    <xsl:when test="boolean(@stroke-width) and not(@stroke-width='')">  
                        <xsl:value-of select="@stroke-width"/>
                    </xsl:when>   
                    <xsl:otherwise>
                        <xsl:text>3</xsl:text>
                    </xsl:otherwise>
                </xsl:choose> 
            </xsl:attribute> 
            
            <xsl:attribute name="stroke">
                <xsl:choose>
                    <xsl:when test="boolean(@on) and not(normalize-space(@on)='')"> 
                        <xsl:choose>
                            <xsl:when test="boolean(@stroke) and not(@stroke='')">  
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
                            <xsl:when test="boolean(@stroke) and not(@stroke='')">  
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
            <xsl:when test="boolean(@on) and not(@on='')">           
                <path fill="none">    
                    
                    <xsl:attribute name="d">
                        <xsl:choose>                              
                            <xsl:when test="boolean(@d) and not(@d='')">  
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
                            <xsl:when test="boolean(@stroke-width) and not(@stroke-width='')">  
                                <xsl:value-of select="@stroke-width div 1.5"/>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>1</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose> 
                    </xsl:attribute> 

            
                    <xsl:attribute name="stroke">
                        <xsl:choose>
                            <xsl:when test="boolean(@off-stroke) and not(@off-stroke='')">  
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
            <xsl:when test="(boolean(@translate-x) and not(normalize-space(@translate-x)='')) and  (boolean(@translate-y) and not(normalize-space(@translate-y)=''))">
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
            <xsl:when test="(boolean(@translate-x) and not(normalize-space(@translate-x)=''))">  
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
            <xsl:when test="(boolean(@translate-y) and not(normalize-space(@translate-y)=''))"> 
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
            <xsl:when test=" (boolean(@rotate-angle) and not(normalize-space(@rotate-angle)='')) or (boolean(@rotate-angle-binding) and not(normalize-space(@rotate-angle-binding)='')) ">
                <xsl:variable name="rotate-x"> 
                    <xsl:choose>
                        <xsl:when test=" (boolean(@rotate-x) and not(normalize-space(@rotate-x)='')) ">
                            <xsl:value-of select="@rotate-x"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>0</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable>
                <xsl:variable name="rotate-y"> 
                    <xsl:choose>
                        <xsl:when test=" (boolean(@rotate-y) and not(normalize-space(@rotate-y)='')) ">
                            <xsl:value-of select="@rotate-y"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:text>0</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:variable> 
                
                
                <xsl:choose>
                    <xsl:when test="(boolean(@rotate-angle) and not(normalize-space(@rotate-angle)='')) and (boolean(@rotate-angle-binding) and not(normalize-space(@rotate-angle-binding)='')) ">            
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
                    <xsl:when test="(boolean(@rotate-angle) and not(normalize-space(@rotate-angle)=''))">            
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
                    <xsl:when test="(boolean(@rotate-angle-binding) and not(normalize-space(@rotate-angle-binding)='')) ">            
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
            <xsl:when test="(boolean(@scale) and not(normalize-space(@scale)='')) and (boolean(@scale-binding) and not(normalize-space(@scale-binding)='')) ">            
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
            <xsl:when test="(boolean(@scale) and not(normalize-space(@scale)=''))">            
                <xsl:attribute name="transform">
                    <xsl:text>scale(</xsl:text>
                    <xsl:value-of select="@scale"/>
                    <xsl:text>)</xsl:text>
                </xsl:attribute>    
                <xsl:apply-templates/>
            </xsl:when>
            <xsl:when test="(boolean(@scale-binding) and not(normalize-space(@scale-binding)='')) ">            
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
            
            <xsl:call-template name="apply_rect"/>
            <xsl:call-template name="apply_id"/>            
            <xsl:call-template name="apply_mlib_schema"/>
            <xsl:call-template name="apply_lib_mouseevent"/> 
            <xsl:attribute name="isgoupelement">
                <xsl:text>true</xsl:text>
            </xsl:attribute>
            
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
    
    

    
</xsl:stylesheet>
