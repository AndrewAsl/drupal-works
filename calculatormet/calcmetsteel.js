/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    Drupal.behaviors.calcmetSteel = {
        'attach': function(context, settings) {
            
            
        var PreventEnter = function(){    
            $('input#edit-steel-length').keypress( function(e){
                    if (e.keyCode === 13){                        
                        var cat = $('select#edit-cat option:selected').text();
                        if (cat === 'Калиброванная круглая'){
                            var mass = $(this).val() * $('span#krmassonem').text();
                            $('div#masscalcul').text(mass);
                        }
                        else if (cat === ' Кованая круглая'){
                            var value = $('select#edit-steel-kovkroptions option:selected');
                            var mass = $(this).val() * $('span#kovkrmassonem').text();  
                            var csadraw = $('input#edit-steel-length').val() * parseFloat(value.text()) * 0.001 * 3.14;
                            $('div#masscalcul').text(mass);
                            $('div#csadraw').text(csadraw);
                        }
                        else if (cat === 'Кованая квадратная'){
                            var value = $('select#edit-steel-kovkvoptions option:selected');
                            var mass = $(this).val() * $('span#massonem').text();  
                            var csadraw = $(this).val() * parseFloat(value.text()) * 0.001 * 4;
                            $('div#kovkvmasscalcul').text(mass);
                            $('div#kovkvcsadraw').text(csadraw);
                        }
                        e.preventDefault();
                    }
                   
            });
        };
            
            
            var CalculateAndPlace = function (){
                $('input#edit-steel-length').change(function(){
                    var cat = $('select#edit-cat option:selected').text();
                    if (cat === 'Калиброванная круглая'){
                        var mass = $(this).val() * $('span#krmassonem').text();
                        $('div#masscalcul').text(mass);
                    } else if (cat === ' Кованая круглая'){
                        var value = $('select#edit-steel-kovkroptions option:selected');
                        var mass = $(this).val() * $('span#kovkrmassonem').text();  
                        var csadraw = $(this).val() * parseFloat(value.text()) * 0.001 * 3.14;
                        $('div#masscalcul').text(mass);
                        $('div#csadraw').text(csadraw);
                    } else if (cat === 'Кованая квадратная'){
                        var value = $('select#edit-steel-kovkvoptions option:selected');
                        var mass = $(this).val() * $('span#massonem').text();  
                        var csadraw = $(this).val() * parseFloat(value.text()) * 0.001 * 4;
                        $('div#kovkvmasscalcul').text(mass);
                        $('div#kovkvcsadraw').text(csadraw);
                    } else {
                        return;
                    }
              });
            };
            
            var GetInfo = function(basename, value){
                value.each(function(){
                  $.post('/services/calcmet/steel/steel_change_info', 
                  {'steelname': basename, 'option': value.val()}, 
                  function(data){
                      if(basename === 'krug'){
                          $('span#krcsa').text(data.csa);
                          $('span#krmassonem').text(data.massonem);
                            if($('input#edit-steel-length').val()){
                              var mass = $('input#edit-steel-length').val() * data.massonem;  
                              $('div#masscalcul').text(mass);
                            } else {
                               $('div#masscalcul').text(''); 
                            }
                      } else if (basename === 'kovkrug'){
                          $('span#kovkrcsa').text(data.csa);
                          $('span#kovkrmassonem').text(data.massonem);
                            if($('input#edit-steel-length').val()){
                              var mass = $('input#edit-steel-length').val() * data.massonem;  
                              var csadraw = $('input#edit-steel-length').val() * parseFloat(value.text()) * 0.001 * 3.14;  
                              $('div#masscalcul').text(mass);
                              $('div#csadraw').text(csadraw);
                            } else {
                               $('div#masscalcul').text(''); 
                               $('div#csadraw').text(''); 
                            }
                      } else if (basename === 'kovkvadrat'){
                          $('span#kovkvcsa').text(data.csa);
                          $('span#massonem').text(data.massonem);
                            if($('input#edit-steel-length').val()){
                              var mass = $('input#edit-steel-length').val() * data.massonem;  
                              var csadraw = $('input#edit-steel-length').val() * parseFloat(value.text()) * 0.001 * 4;  
                              $('div#kovkvmasscalcul').text(mass);
                              $('div#kovkvcsadraw').text(csadraw);
                            } else {
                               $('div#kovkvmasscalcul').text(''); 
                               $('div#kovkvcsadraw').text(''); 
                            }
                      };
                  });
              });
            };
            
            var ChangeOptions = function(){
                var name = $('select[id^="edit-steel"]');
                name.on('change', function(){
                    if (name[0].id === 'edit-steel-kroptions'){
                        GetInfo('krug', $('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();
                        
                    } else if (name[0].id === 'edit-steel-kovkroptions'){
                        GetInfo('kovkrug',$('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();
                       
                    } else if (name[0].id === 'edit-steel-kovkvoptions'){
                       GetInfo('kovkvadrat', $('select#'+ name[0].id +' option:selected'));
                       PreventEnter();
                       CalculateAndPlace();
                       
                    } else {
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
                    if (cat === 'Калиброванная круглая'){
                        title = 'Сталь ' + cat.toLowerCase() + ' диаметром ' + $('select#edit-steel-kroptions option:selected').text();
                        dlinaintbl = $('#edit-steel-length').val();
                        massintbl = $('#masscalcul').text();
                        if (title && dlinaintbl && massintbl){
                            html = '<tr><td>'+ numpp +'</td>'
                                +'<td>' + title + '</td>' 
                                +'<td>'+ dlinaintbl + '</td>' 
                                +'<td>'+massintbl+'</td>'
                                +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
                            $('table#spec').append(html);
                        } else {
                            alert ('Необходимо заполнить все данные');
                            return false;
                        }                        
                    }
                    else if (cat === ' Кованая круглая'){
                        title = 'Сталь ' + cat.toLowerCase() + ' диаметром ' + $('select#edit-steel-kovkroptions option:selected').text();
                        dlinaintbl = $('#edit-steel-length').val();
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
                    }
                    else if (cat === 'Кованая квадратная'){
                        title = 'Сталь ' + cat.toLowerCase() + ' со стороной ' + $('select#edit-steel-kovkvoptions option:selected').text();
                        dlinaintbl = $('#edit-steel-length').val();
                        massintbl = $('#kovkvmasscalcul').text();
                        csadraw = $('#kovkvcsadraw').text();
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
                    }                    
                    var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> <button class="btn btn-success" type="submit">Добавить в личный кабинет</button></div>';
                       if(!$('div#btncab').length) 
                        $('#edit-steel-spec').append(btn);
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
            
            $('select#edit-cat', context).on('change', function(e){
                e.stopPropagation();
                $('select#edit-cat option:selected').each(
                    function(){
                      $.post('/services/calcmet/steel/steel_change_options', {'ajaxsteelchangeoptions': $(this).val()}, function(data){
                          $('section#block-system-main form:last').replaceWith(data);
                      })
                      .always(function(){ ChangeOptions(); CalculateAndPlace(); PreventEnter(); AddToSpec();});  
                    }
                );
            });     
            
            CalculateAndPlace();
            PreventEnter();
            ChangeOptions();
            AddToSpec();
        }       
  };         
})(jQuery);

