<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns="http://www.w3.org/2000/svg"
xmlns:mlib="http://dvnci/mlib"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:html="http://www.w3.org/TR/xhtml1"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
extension-element-prefixes="mlib">
    
    <xsl:import href="mainlibstyle.xsl"/>

    <xsl:template name="mainlib">
        
        <script type="text/javascript" xlink:href="../mainlib/js/mainlibutil.js"></script>
        <script type="text/javascript" xlink:href="../mainlib/js/redactor.js"></script> 
        <script type="text/javascript" xlink:href="../mainlib/js/mainlib.js"></script>

        
        <xsl:call-template name="apply_mlib_armatfilter"/>
        <xsl:call-template name="apply_mlib_style"/>
          
    </xsl:template>
    
      
    <xsl:template name="apply_mlib_schema">    
        <xsl:attribute name="xsi:schemaLocation">
            <xsl:text>../mainlib/maillib.xsd</xsl:text>
        </xsl:attribute>  
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
            <xsl:when test="boolean(@type) and not(@type='')">                             
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
            <xsl:when test="(boolean(@off) and not(@off='')) and (boolean(@on) and not(@on=''))">
                <xsl:text>(!(</xsl:text>
                <xsl:value-of select="@on"/>
                <xsl:text>).valid  &#38;&#38; !(</xsl:text>
                <xsl:value-of select="@off"/>
                <xsl:text>).valid) ? 'none' : </xsl:text>
                               
            </xsl:when>
            <xsl:when test="boolean(@off) and not(@off='')">
                <xsl:text>(!(</xsl:text>
                <xsl:value-of select="@off"/>
                <xsl:text>).valid) ? 'none' : </xsl:text>
            </xsl:when>
            <xsl:when test="boolean(@on) and not(@on='')">
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
                <xsl:when test="(boolean(@local) and not(@local=''))"> 
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
                <xsl:when test="(boolean(@local) and not(@local=''))"> 
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
                <xsl:when test="(boolean(@local) and not(@local=''))"> 
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
            <xsl:when test="(boolean(@off) and not(@off='')) or (boolean(@on) and not(@on=''))">
                <xsl:choose>                        
                    <xsl:when test="(boolean(@roff) and not(@roff='')) or (boolean(@ron) and not(@ron='')) or (boolean(@rauto) and not(@rauto=''))">
                        <xsl:choose>                        
                            <xsl:when test="(boolean(@rauto) and not(@rauto='')) and (boolean(@auto) and not(@auto=''))">
                                <xsl:call-template name="apply_mlib_aratura_cursor_autocontrol"/>
                            </xsl:when>
                            <xsl:when test="(boolean(@auto) and not(@auto=''))">
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
                <xsl:value-of select="@environment"/> 
            </xsl:variable>
            <xsl:attribute name="filter">
                <xsl:text>url(#armat_filter1)</xsl:text>
            </xsl:attribute>     
            <xsl:choose>                        
                <xsl:when test="(boolean(@on) and not(@on='')) and (boolean(@off) and not(@off=''))"> 
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
                <xsl:when test="boolean(@on) and not(@on='')"> 
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
                <xsl:when test="boolean(@off) and not(@off='')"> 
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
            <xsl:when test="boolean(@local) and not(@local='')">
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
            <xsl:when test="boolean(@auto) and not(@auto='')">
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
            <xsl:when test="boolean(@control) and not(@control='')">
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
            <xsl:when test="boolean(@don) and not(@don='')"> 
                <g>
                    <xsl:attribute name="style">
                        <xsl:choose>                          
                            <xsl:when test="boolean(@on) and not(@on='')">                                               
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
            <xsl:when test="boolean(@doff) and not(@doff='')"> 
                <g>
                    <xsl:attribute name="style">
                        <xsl:choose>                          
                            <xsl:when test="boolean(@off) and not(@off='')">                                                 
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
            <xsl:when test="(boolean(@alarm) and not(@alarm=''))">
                <g  class="alarm" opacity="0.3">              
                    <xsl:attribute name="display">
                        <xsl:text>#{ min(</xsl:text>
                        <xsl:value-of select="@alarm"/>
                        <xsl:text> , (</xsl:text>
                        <xsl:value-of select="@alarm"/>
                        <xsl:text>).valid </xsl:text>
                        <xsl:text>)   ? 'block'  : </xsl:text>
                        <xsl:choose>                
                            <xsl:when test="(boolean(@alarmack) and not(@alarmack=''))">
                                <xsl:text> ((min(</xsl:text>
                                <xsl:value-of select="@alarmack"/>
                                <xsl:text> , (</xsl:text>
                                <xsl:value-of select="@alarmack"/>
                                <xsl:text>).valid))   ? 'block'  : 'none')  }</xsl:text>
                            </xsl:when>   
                            <xsl:otherwise>
                                <xsl:text>    'none'  } </xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>                            
                    <circle cx="500" cy="500" r="500"/>
                    <animate  attributeType="XML" attributeName="opacity" from="0.1" to="0.99" dur="500ms" calcMode = "linear" repeatCount="indefinite">
                        <xsl:choose>                
                            <xsl:when test="(boolean(@alarmack) and not(@alarmack=''))">
                                <xsl:attribute name="to">
                                    <xsl:text>#{ (</xsl:text>
                                    <xsl:value-of select="@alarmack"/>
                                    <xsl:text>)   ? '0.1'  : '0.99' }</xsl:text>
                                </xsl:attribute> 
                            </xsl:when>
                        </xsl:choose>
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
                        <xsl:when test="not(boolean(@type)) or (@type='motorD') or (@type='motor') or (@type='')">
                            <xsl:text>motor</xsl:text>
                        </xsl:when> 
                        <xsl:otherwise>
                            <xsl:text>valve</xsl:text>
                        </xsl:otherwise>    
                    </xsl:choose>        
                </xsl:variable>
                <xsl:choose>             
                    <xsl:when test="boolean(@rauto) and not(@rauto='')">   
                        <xsl:attribute name="onclick">
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                            <xsl:text>mainlib.armatura_auto_popup(this, '</xsl:text>
                            <xsl:value-of select="@header"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="$armaturakind"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@on"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@off"/>
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
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="onclick">
                            <xsl:text>if (this.getAttribute('cursor')=='pointer') {</xsl:text> 
                            <xsl:text>mainlib.armatura_popup(this, '</xsl:text>
                            <xsl:value-of select="@header"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="$armaturakind"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@on"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@off"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@ron"/>
                            <xsl:text>','</xsl:text>
                            <xsl:value-of select="@roff"/>
                            <xsl:text>'</xsl:text>
                            <xsl:text>);};</xsl:text>
                        </xsl:attribute>  
                    </xsl:otherwise>                            
                </xsl:choose>
            </xsl:when>               
        </xsl:choose>
    </xsl:template>  
    
    <!--
    
    формирование стиля
    
    -->    
    
    
    <!--xsl:template name="apply_mlib_aratura_style">
        <style type="text/css">
            <xsl:text>  
            
            </xsl:text>
            <xsl:text>  g#</xsl:text>
            <xsl:value-of select="@id"/>
            <xsl:text> {</xsl:text>
            <xsl:text>     
                cursor: pointer;}
            </xsl:text>
            <xsl:text> 
                
            </xsl:text>
            <xsl:text>  g#</xsl:text>
            <xsl:value-of select="@id"/>
            <xsl:text>[state="disable"] {</xsl:text>
            <xsl:text>     
                cursor: none;}
            </xsl:text>
            <xsl:text> 
            </xsl:text>
        </style>   
    </xsl:template-->
  
  
        <!--
    
    Основной обработчик
    
    -->
      
    
    <xsl:template match="//mlib:armatura" >   
        <g>       
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template  name="apply_visible"/>
                                                                   
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
            
            <!--xsl:call-template name="apply_mlib_aratura_style"/-->
            
                        
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
                <xsl:when test="(boolean(@param) and not(@param=''))">
                    <xsl:choose> 
                        <xsl:when test="(boolean(@type) and (@type='tumbler'))">
                            <xsl:text>dvnci_exec('((</xsl:text>
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
                            <xsl:text>dvnci_exec('</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>');</xsl:text>                               
                        </xsl:when> 
                        <xsl:when test="(not(boolean(@type)) or (@type=''))">
                            <xsl:text>dvnci_exec('</xsl:text>
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
                <xsl:when test="(boolean(@param) and not(@param=''))">
                    <xsl:choose> 
                        <xsl:when test="(boolean(@type) and (@type='impulse'))">
                            <xsl:text>dvnci_exec('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; </xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 0) : (0</xsl:text>                           
                            <xsl:text>))');</xsl:text>
                        </xsl:when>
                        <xsl:when test="(boolean(@type) and (@type='unimpulse'))">
                            <xsl:text>dvnci_exec('((</xsl:text>
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
                <xsl:when test="(boolean(@param) and not(@param=''))">
                    <xsl:choose> 
                        <xsl:when test="(boolean(@type) and (@type='impulse'))">
                            <xsl:text>dvnci_exec('((</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>).valid &#38;&#38; !</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> ? (</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text> @ 1) : (0</xsl:text>                           
                            <xsl:text>))');</xsl:text>
                        </xsl:when>
                        <xsl:when test="(boolean(@type) and (@type='unimpulse'))">
                            <xsl:text>dvnci_exec('((</xsl:text>
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
            <xsl:when test="(boolean(@onclick) and not(@onclick=''))">      
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
            <xsl:when test="(boolean(@ondblclick) and not(@ondblclick=''))">      
                <xsl:attribute name="ondblclick">
                    <xsl:text> if (this.getAttribute('state')!='disable') {</xsl:text> 
                    <xsl:value-of select="@ondblclick"/>
                    <xsl:text>;</xsl:text>
                    <xsl:text> };</xsl:text>                       
                </xsl:attribute>
            </xsl:when>
        </xsl:choose>
        
        <xsl:choose>                
            <xsl:when test="(boolean(@onmouseup) and not(@onmouseup=''))">      
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
            <xsl:when test="(boolean(@onmousedown) and not(@onmousedown=''))">      
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
                <xsl:when test="(boolean(@disable) and not(@disable=''))">                                    
                    <xsl:choose>                   
                        <xsl:when test="(boolean(@state) and not(@state=''))">   
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
                        <xsl:when test="(boolean(@state) and not(@state=''))">                                        
                            <!--xsl:text>#{ (</xsl:text>
                            <xsl:value-of select="@state"/>
                            <xsl:text>) ? 'off' : '' :default }</xsl:text-->
                            <xsl:text>#{ m1::c1 ? 'off' : 'on'}</xsl:text>
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
                <xsl:when test="(boolean(@dsblcolor1) and not(@dsblcolor1=''))">
                    <xsl:value-of select="@dsblcolor1"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>#777</xsl:text>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable>
        
        <xsl:variable name="var_dsblcolor2">
            <xsl:choose>
                <xsl:when test="(boolean(@dsblcolor2) and not(@dsblcolor2=''))">
                    <xsl:value-of select="@dsblcolor2"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:text>#AAA</xsl:text>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable>
        
        <xsl:variable name="var_fontstyle">
            <xsl:choose>
                <xsl:when test="(boolean(@fontstyle) and not(@fontstyle=''))">
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
                <xsl:when test="(boolean(@offfontstyle) and not(@offfontstyle=''))">
                    <xsl:value-of select="@offfontstyle"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$var_fontstyle"/>
                </xsl:otherwise>     
            </xsl:choose> 
        </xsl:variable> 
        
        <xsl:variable name="var_dsblfontstyle">
            <xsl:choose>
                <xsl:when test="(boolean(@dsblfontstyle) and not(@dsblfontstyle=''))">
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
            <xsl:when test="(boolean(@oncaption) and not(@oncaption=''))">
                <xsl:choose>
                    <xsl:when test="(boolean(@dsblcaption) and not(@dsblcaption=''))">                       
                        <xsl:choose>
                            <xsl:when test="(boolean(@state) and not(@state=''))">
                                <xsl:choose>
                                    <xsl:when test="(boolean(@disable) and not(@disable=''))">                                
                                        <xsl:call-template name="apply_mlib_button_caption_value_both"/>                               
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:call-template name="apply_mlib_button_caption_value_state"/>                      
                                    </xsl:otherwise>     
                                </xsl:choose>                                                                                               
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:choose>
                                    <xsl:when test="(boolean(@disable) and not(@disable=''))">                                
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
                            <xsl:when test="(boolean(@state) and not(@state=''))">
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
                    <xsl:when test="(boolean(@dsblcaption) and not(@dsblcaption=''))">                       
                        <xsl:choose>
                            <xsl:when test="(boolean(@disable) and not(@disable=''))">                              
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
            
            <xsl:call-template name="apply_mlib_button_control"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template  name="apply_visible"/>
                     
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
    
    
    <xsl:template match="//mlib:bitbutton" >   
        <g>       
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template  name="apply_visible"/>

            <rect role="button"  aria-pressed="true" class="disablebuttongrad">
                <xsl:attribute name="onmouseover">
                    <xsl:text>if (event.toElement==this) {this.setAttribute('style','stroke-width : 1; stroke : red;')};</xsl:text>
                </xsl:attribute>
                <xsl:attribute name="onmouseout">
                    <xsl:text>if (event.fromElement==this) {this.setAttribute('style','stroke-width : 0; stroke : trasparent;')};</xsl:text>
                </xsl:attribute>  
                <xsl:choose>                
                    <xsl:when test="(boolean(@param) and not(@param=''))">  
                        <xsl:attribute name="onclick">                   
                            <xsl:text>dvnci_exec('</xsl:text>
                            <xsl:value-of select="@param"/>
                            <xsl:text>');</xsl:text>
                        </xsl:attribute> 
                    </xsl:when>
                </xsl:choose> 
                <xsl:call-template name="apply_rect"/>
                <xsl:call-template name="apply_r"/>

            </rect> 
            
            <svg>                
                <xsl:call-template name="apply_rect"/>
                <text class="central_svgnatext">
                    <xsl:attribute name="x">
                        <xsl:value-of select="@width div 2"/>
                    </xsl:attribute>
                    <xsl:attribute name="y">
                        <xsl:value-of select="@height div 2"/>
                    </xsl:attribute>
                    <xsl:choose>                
                        <xsl:when test="(boolean(@fontstyle) and not(@fontstyle=''))">
                            <xsl:attribute name="style">
                                <xsl:value-of select="@fontstyle"/>
                            </xsl:attribute>
                        </xsl:when>
                    </xsl:choose>     
                    <xsl:value-of select="@caption"/>
                </text>
            </svg>       
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
    
   
    
    
    <xsl:template match="//mlib:rect" >
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template  name="apply_visible"/>
            
            <xsl:variable name="landsc">
                <xsl:choose>
                    <xsl:when test="boolean(@direction='tb') or boolean(@direction='bt')">v</xsl:when> 
                    <xsl:otherwise>h</xsl:otherwise>  
                </xsl:choose>
            </xsl:variable>
  
            
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
                
                
                
                <!-- Fill background-->
                
                <xsl:choose>
                    <xsl:when test=" not(@background='')">  
                        <xsl:choose>
                            <xsl:when test="(@background='gaz') or (@background='water') or (@background='air') or (@background='oil') or (@background='stream')">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="@background"/>
                                    <xsl:text>grad</xsl:text>
                                    <xsl:value-of select="$landsc"/>
                                </xsl:attribute>     
                            </xsl:when> 
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:value-of select="@background"/>
                                </xsl:attribute>    
                            </xsl:otherwise>                           
                        </xsl:choose>    
                    </xsl:when>
                    <xsl:otherwise>                
                        <xsl:attribute name="class">
                            <xsl:text>nongrad</xsl:text>
                            <xsl:value-of select="$landsc"/>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                

            </rect>
            
            <!-- Interactive geometry-->
            
            <rect >
                
                
                <!-- Direction-->     
                
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
                            <xsl:value-of select="@value"/>
                            <xsl:text> - </xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.mineu)/</xsl:text>
                            <xsl:text>(</xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.maxeu - </xsl:text>
                            <xsl:value-of select="@value"/>
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
                            <xsl:value-of select="@value"/>
                            <xsl:text> - </xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.mineu)/</xsl:text>
                            <xsl:text>(</xsl:text>
                            <xsl:value-of select="@value"/>
                            <xsl:text>.maxeu - </xsl:text>
                            <xsl:value-of select="@value"/>
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
                
                <xsl:choose>
                    <xsl:when test="not(@fill='')">  
                        <xsl:choose>
                            <xsl:when test="(@fill='gaz') or (@fill='water') or (@fill='air') or (@fill='oil') or (@fill='stream')">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="@fill"/>
                                    <xsl:text>grad</xsl:text>
                                    <xsl:value-of select="$landsc"/>
                                </xsl:attribute> 
                            </xsl:when> 
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:value-of select="@fill"/>
                                </xsl:attribute>    
                            </xsl:otherwise>                                     
                        </xsl:choose>    
                    </xsl:when>
                    <xsl:otherwise>                
                        <xsl:attribute name="class">
                            <xsl:text>nongrad</xsl:text>
                            <xsl:value-of select="$landsc"/>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                
                
            </rect>                
                

        

        
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
    
    
    <xsl:template match="//mlib:sensor" >
        <g>
            
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            
            <xsl:call-template name="apply_rect"/>
            
            <xsl:call-template name="apply_cental_rotate"/>
            
            <xsl:call-template  name="apply_visible"/>
            
            <xsl:choose>
                <xsl:when test="boolean(@param) and not(@param='')">
                    <xsl:attribute name="onclick">
                        <xsl:text>main_label_click('</xsl:text>
                        <xsl:value-of select="@param"/>
                        <xsl:text>')</xsl:text>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose>
            
      
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
                
                
                
                <!-- Fill background-->
                
                <xsl:choose>
                    <xsl:when test=" not(@background='')">  
                        <xsl:choose>
                            <xsl:when test="(@background='gaz') or (@background='water') or (@background='air') or (@background='oil') or (@background='stream')">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="@background"/>
                                    <xsl:text>gradh</xsl:text>
                                </xsl:attribute>     
                            </xsl:when> 
                            <xsl:otherwise> 
                                <xsl:attribute name="fill">
                                    <xsl:value-of select="@background"/>
                                </xsl:attribute>    
                            </xsl:otherwise>                           
                        </xsl:choose>    
                    </xsl:when>
                    <xsl:otherwise>                
                        <xsl:attribute name="class">
                            <xsl:text>blackgradh</xsl:text>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                
 
                

            </rect>
                
            <xsl:choose>
                <xsl:when test="boolean(@param) and not(@param='')">
                    <svg>
                        <xsl:call-template name="apply_rect"/>
                        <text>
                            
                            <xsl:choose>
                                <xsl:when test="boolean(@alighn) and (@alighn='left')">               
                                    <xsl:attribute name="x">
                                        <xsl:value-of select="@width * 0.1 "/>
                                    </xsl:attribute>
                                    <xsl:attribute name="y">
                                        <xsl:value-of select="@height div 2"/>
                                    </xsl:attribute> 
                                    <xsl:attribute name="class">
                                        <xsl:text>left_svgnatext</xsl:text>
                                    </xsl:attribute>
                                </xsl:when>
                                <xsl:when test="boolean(@alighn) and (@alighn='center')">               
                                    <xsl:attribute name="x">
                                        <xsl:value-of select="@width div 2"/>
                                    </xsl:attribute>
                                    <xsl:attribute name="y">
                                        <xsl:value-of select="@height div 2"/>
                                    </xsl:attribute> 
                                    <xsl:attribute name="class">
                                        <xsl:text>central_svgnatext</xsl:text>
                                    </xsl:attribute>
                                </xsl:when>
                                <xsl:otherwise>   
                                    <xsl:attribute name="x">
                                        <xsl:value-of select="@width * 0.9 "/>
                                    </xsl:attribute>
                                    <xsl:attribute name="y">
                                        <xsl:value-of select="@height div 2"/>
                                    </xsl:attribute> 
                                    <xsl:attribute name="class">
                                        <xsl:text>right_svgnatext</xsl:text>
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
                                
                            <xsl:choose>                              
                                <xsl:when test="boolean(@format) and not(@format='')">
                                    <xsl:text>#{ format(</xsl:text>
                                    <xsl:value-of select="@param"/>
                                    <xsl:text> , '</xsl:text>
                                    <xsl:value-of select="@format"/>
                                    <xsl:text>')}</xsl:text>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:text>#{ format(</xsl:text>
                                    <xsl:value-of select="@param"/>
                                    <xsl:text> , '%8.1f')}</xsl:text>                                       
                                </xsl:otherwise>
                            </xsl:choose>
                            

                            
                        </text>
                    </svg>
                </xsl:when>
            </xsl:choose>                   
            
            <!-- Interactive geometry-->
 
 


        
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
    
    <xsl:template match="//mlib:path" >
        <g>    
            <xsl:call-template name="apply_id"/>
            
            <xsl:call-template name="apply_mlib_schema"/>
            <path>

            
                <xsl:attribute name="d">
                    <xsl:choose>                              
                        <xsl:when test="boolean(@d) and not(@d='')">  
                            <xsl:value-of select="@d"/>
                        </xsl:when>   
                        <xsl:otherwise> </xsl:otherwise>
                    </xsl:choose>    
                </xsl:attribute>
            
            <!--xsl:attribute name="filter">
                                <xsl:text>url(#tubefilter)</xsl:text>
            </xsl:attribute-->
            
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

                <xsl:attribute name="fill">
                    <xsl:choose>
                        <xsl:when test="boolean(@fill) and not(@fill='')">  
                            <xsl:value-of select="@fill"/>
                        </xsl:when>   
                        <xsl:otherwise>
                            <xsl:text>none</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:attribute>
            
                <xsl:attribute name="stroke">
                    <xsl:choose>
                        <xsl:when test="boolean(@stroke) and not(@stroke='')">  
                            <xsl:value-of select="@stroke"/>
                        </xsl:when>   
                        <xsl:otherwise>
                            <xsl:text>black</xsl:text>
                        </xsl:otherwise>
                    </xsl:choose> 
                </xsl:attribute>
            
            </path>
            
            <xsl:choose>
                <xsl:when test="boolean(@on) and not(@on='')">           
                    <path>          
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
                            <xsl:text>  ? 'display: none;' :  'display: block;'</xsl:text>
                            <xsl:text>}</xsl:text>
                        </xsl:attribute>

            
                        <xsl:attribute name="stroke-width">
                            <xsl:choose>
                                <xsl:when test="boolean(@stroke-width) and not(@stroke-width='')">  
                                    <xsl:value-of select="@stroke-width div 1.5"/>
                                </xsl:when>   
                                <xsl:otherwise>
                                    <xsl:text>1px</xsl:text>
                                </xsl:otherwise>
                            </xsl:choose> 
                        </xsl:attribute> 

                        <xsl:attribute name="fill">

                            <xsl:text>none</xsl:text>

                        </xsl:attribute>
            
                        <xsl:attribute name="stroke">

                            <xsl:text>black</xsl:text>

                        </xsl:attribute>
            
                    </path>
                </xsl:when>        
            </xsl:choose>
            
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
                    <script xmlns="http://www.w3.org/1999/xhtml"  type="text/javascript" src="../mainlib/js/mainlibutil.js"></script>

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

                <body>
                    <xsl:attribute name="xmlns">                    
                        <xsl:text>http://www.w3.org/1999/xhtml</xsl:text>
                    </xsl:attribute>  
                    <xsl:attribute name="style">                    
                        <xsl:value-of select="$rectvarw"/>
                        <xsl:value-of select="$rectvarh"/>
                    </xsl:attribute>  
                    <div xmlns="http://www.w3.org/1999/xhtml">
                        <table>
                            <xsl:attribute name="xmlns">                    
                                <xsl:text>http://www.w3.org/1999/xhtml</xsl:text>
                            </xsl:attribute>  
                            <xsl:attribute name="style">                    
                                <xsl:value-of select="$rectvarw"/>
                                <xsl:value-of select="$rectvarfont"/>
                            </xsl:attribute>  
                            <script type="text/javascript">                           
                                <xsl:text>var testsalarm=new mainlibutil.alarmtable(this.document.getElementById('</xsl:text>
                                <xsl:value-of select="@id"/>
                                <xsl:text>'));</xsl:text>
                            </script>
                            <tbody xmlns="http://www.w3.org/1999/xhtml">       
                                <tr>
                                    <xsl:attribute name="xmlns">                    
                                        <xsl:text>http://www.w3.org/1999/xhtml</xsl:text>
                                    </xsl:attribute>  
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

</xsl:stylesheet>
