/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    Drupal.behaviors.calcmetSteel = {
        'attach': function(context, settings) {
        
            var csa = 0.016;
            

            var PreventEnter = function(){    
                $('input#edit-roundprokat-length').keypress( function(e){
                    if (e.keyCode === 13){                        
                            var mass = $(this).val() * $('span#massonem').text();
                            var csadraw = $(this).val() * csa;
                            $('div#masscalcul').text(mass);
                            $('div#csadraw').text(csadraw);
                            e.preventDefault();
                        }                        
                    }
                );
            };
            
            var CalculateAndPlace = function (){
                $('input#edit-roundprokat-length').change(function(){
                        var mass = $(this).val() * $('span#massonem').text();
                        var csadraw = $(this).val() * csa;
                        $('div#masscalcul').text(mass);
                        $('div#csadraw').text(csadraw);
                    });
            };
            
            var GetInfo = function(basename, value){
                //csa = SetCsa();
                value.each(function(){
                  $.post('/services/calcmet/roundprokat/roundprokat_change_info', 
                  {'roundprokatname': basename, 'option': value.val()}, 
                  function(data){
                      
                        /*$('span#diametr').text(data.diametr);
                        $('span#razmer1').text(data.storona1);
                        $('span#razmer2').text(data.storona2);
                        $('span#thickness').text(data.thick);*/
                        $('span#massonem').text(data.massonem);
                        $('span#csa').text(data.csatext);
                        csa = data.csa;
                        //console.log(csa);
                        if($('input#edit-roundprokat-length').val()){
                          var mass = $('input#edit-roundprokat-length').val() * data.massonem;  
                          var csadraw = $('input#edit-roundprokat-length').val() * csa;  
                          $('div#masscalcul').text(mass);
                          $('div#csadraw').text(csadraw);
                        } else {
                           $('div#masscalcul').text(''); 
                           $('div#csadraw').text(''); 
                        }                      
                  });
              });
            };
            
            var ChangeOptions = function(){
                var name = $('select[id^="edit-roundprokat"]');
                name.on('change', function(){
                    if (name[0].id === 'edit-roundprokat-roundprokatnames'){                  
                        GetInfo('roundprokat', $('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();
                        
                    }                
                    else {
                        return;
                    }
                });
            };
            
            var AddToSpec = function(){
                var btntospec = $('#btnspec button');
                btntospec.on('click', function(e){
                    e.preventDefault();
                    //alert ('click');
                    var cat = $('select#edit-cat option:selected').text();
                    var numpp = $('table#spec tr').length;
                    var title, dlinaintbl, massintbl, csadraw, html;
                        title = 'Диаметр проката ' + $('select[id^=edit-roundprokat] option:selected').text();
                        dlinaintbl = $('#edit-roundprokat-length').val();
                        massintbl = $('#masscalcul').text();
                        csadraw = $('#csadraw').text();
                        if (title && dlinaintbl && massintbl && csadraw){
                            html = '<tr><td>'+ numpp +'</td>'
                                +'<td>' + title + '</td>' 
                                +'<td>'+ dlinaintbl + '</td>' 
                                +'<td>'+massintbl+'</td>'
                                +'<td>'+csadraw+'</td>'
                                +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
                            $('table#spec').append(html);
                        } else {
                            alert ('Необходимо заполнить все данные');
                            return false;
                        }                                           
                    var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> <button class="btn btn-success" type="submit">Добавить в личный кабинет</button></div>';
                       if(!$('div#btncab').length) 
                        $('#edit-spec').append(btn);
                    //console.log(html);
                    var delrow = $("table#spec .deleterow", context);
                    delrow.on("click",function(e) {
                        e.preventDefault();
                        var tr = $(this).closest('tr');
                        tr.fadeOut(400, function(){
                            tr.remove();
                            if ($('table#spec tr').length === 1){
                                $('div#btncab').remove();
                            }
                        });
                      return false;
                    });
                    $('div#btncab button').one("click",function(e) {
                       //e.preventDefault();
                       alert ('Данные в личный кабинет отправлены' );
                       return false;
                    });
                });
            };
            
            /*$('select#edit-cat', context).on('change', function(e){
                e.stopPropagation();
                var txtForCsa = $('select#edit-cat option:selected').text();
                //console.log (txtForCsa);
                switch (txtForCsa){
                    case 'стальные бесшовные горячедеформированные':
                        csa = 0.0628;
                    break;    
                    case 'стальные электросварные прямошовные':
                        csa = 0.0377;
                    break;    
                    case 'стальные квадратные':
                        csa = 0.04;
                    break;    
                    case 'стальные овальные':
                        csa = 0.01413;
                    break;    
                    case 'стальные прямоугольные':
                        csa = 0.05;
                    break;
                    //console.log(csa);
                }
                $('select#edit-cat option:selected').each(
                    function(){  
                      $.post('/services/calcmet/roundprokat/roundprokat_change_options', {'ajaxroundprokatchangeoptions': $(this).val()}, function(data){
                          $('section#block-system-main form[id^="calcmet-roundprokat"]').replaceWith(data);
                      })
                      .always(function(){ ChangeOptions(); CalculateAndPlace(); PreventEnter(); AddToSpec(); });  
                    }                                    
                );
                
            });*/     
            
            //SetCsa();
            CalculateAndPlace();
            PreventEnter();
            ChangeOptions();
            AddToSpec();
        }       
  };         
})(jQuery);

