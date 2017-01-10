<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Шапка
 */
function set_steel_page(){
    $output = '<div class="row">';
    $output .= render(drupal_get_form('calcmet_undercat_form'));
    $output .= render(drupal_get_form('calcmet_steel_form'));
    $output .= '</div>';
    return $output;
}
function calcmet_undercat_form($form, &$form_state){
    $form['cat'] = array(
        '#title' => t('Категория стального проката'),
        '#type' => 'select',
        '#options' => calcmet_get_undercategory_title('calcmetundercat'),
        '#default_value' => 2,
        //'#size' => 10,
        '#description' => t('Выберите тип стального проката'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'steel_change_cat',
//        ),
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>'  
    );
    $form_state['rebuild'] = TRUE;
    return $form;
}

/*
    Раздел по квадрату
 */
function calcmet_steel_form($form, &$form_state){
    $form = array();
    
    $form['steel'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['steel']['kroptions'] = array(
        '#title' => t('Диаметр, мм'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetsteelkrug'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип полосы'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'steel_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['steel']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'steel_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['steel']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       '#suffix' =>'</div>'
    );
    $form['steel']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/steelkovkr.jpg" width=200px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['steel']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="steel-info">'
        . '<strong>Площадь поперечного сечения, мм2:</strong> <span id="krcsa">7.07</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="krmassonem">0.056</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 7417-75 "Сталь калиброванная круглая. '
        . 'Сортамент" утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3 с учетом изменения №2 '
        .'</div>',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['steel']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['steel']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Название</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        //. '<th>Площадь окраски, м2</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetsteel.js',
    );
    $form['#action'] = url('/services/calcmet/steel');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */
function calcmet_steel_kovkrug_form($form, &$form_state){
    $form = array();    
    
    $form['steel'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['steel']['kovkroptions'] = array(
        '#title' => t('Диаметр, мм'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetsteelkovkrug'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'steel_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['steel']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'steel_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['steel']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['steel']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['steel']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/steelkovkr.jpg" width=200px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['steel']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="steel-info">'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="kovkrcsa">12.57</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="kovkrmassonem">9.86</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 1133-71 "Сталь кованая круглая и квадратная. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 № 3'
        .'</div>',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['steel']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['steel']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Название</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, м2</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetsteel.js',
    );
    $form['#action'] = url('/services/calcmet/steel');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */
function calcmet_steel_kovkvadrat_form($form, &$form_state){
    $form = array();    
    
    $form['steel'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['steel']['kovkvoptions'] = array(
        '#title' => t('Сторона квадрата, мм'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetsteelkovkvadrat'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'steel_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['steel']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'steel_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['steel']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="kovkvmasscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['steel']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="kovkvcsadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['steel']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/steelkovkv.jpg" width=200px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['steel']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="steel-info">'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="kovkvcsa">16</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">12.56</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 1133-71 "Сталь кованая круглая и квадратная. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 № 3'
        .'</div>',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['steel']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['steel']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Название</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, м2</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetsteel.js',
    );
    $form['#action'] = url('/services/calcmet/steel');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */

function steel_change_info(){
    $select = $_POST['option'];
    $basename = $_POST['steelname'];
    //dsm($select);
    switch ($basename) {
        case 'krug':
            $infos = db_select('calcmetsteelkrug', 'sk')
                ->fields('sk', array('skdiametr', 'skcsa', 'skmassonem',))
                ->condition('sk.skdid', $select)
                ->execute()
                ->fetchAll();
            $csa = $infos[0]->skcsa;
            $massonem = $infos[0]->skmassonem;
            drupal_json_output(array(                       
                'csa'=> $csa,                       
                'massonem'=> $massonem,                       
                ));
        break;
        case 'kovkrug':
            $infos = db_select('calcmetsteelkovkrug', 'skk')
                ->fields('skk', array('skkcsa', 'skkmassonem',))
                ->condition('skk.skkdid', $select)
                ->execute()
                ->fetchAll();
            $csa = $infos[0]->skkcsa;
            $massonem = $infos[0]->skkmassonem;
            drupal_json_output(array(                       
                'csa'=> $csa,                       
                'massonem'=> $massonem,                       
                ));
        break;
        case 'kovkvadrat':
            $infos = db_select('calcmetsteelkovkvadrat', 'skovk')
                ->fields('skovk', array('skkvcsa', 'skkvmassonem',))
                ->condition('skovk.skkvdid', $select)
                ->execute()
                ->fetchAll();
            $csa = $infos[0]->skkvcsa;
            $massonem = $infos[0]->skkvmassonem;
            drupal_json_output(array(                       
                'csa'=> $csa,                       
                'massonem'=> $massonem,                       
                ));
        break;

        default:
        break;
    }
           
    drupal_exit();
}

function calcmet_get_undercategory_title($basename){
     $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetundercat':
                if ($entry->ccid == 6){
                    $options[$entry->cucid] = $entry->title;
                }
                break;
            default:
                break;
        }
    }
    return $options;
}

function calcmet_get_options ($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetsteelkrug':
                $options[$entry->skdid] = $entry->skdiametr;
                break;
            case 'calcmetsteelkovkrug':
                $options[$entry->skkdid] = $entry->skkdiametr;
                break;
            case 'calcmetsteelkovkvadrat':
                $options[$entry->skkvdid] = $entry->skkvstorona;
                break;

            default:
                break;
        }
    }
    return $options;
}

function steel_change_options(){
    $select = $_POST['ajaxsteelchangeoptions'];
    switch ($select) {
            case 2:
                $form = drupal_render(drupal_get_form('calcmet_steel_form'));
                
                break;
            case 3:
                $form = drupal_render(drupal_get_form('calcmet_steel_kovkrug_form'));
                break;
            case 4:
                $form = drupal_render(drupal_get_form('calcmet_steel_kovkvadrat_form'));
                break;

            default:
                break;
        }
    drupal_json_output($form);
    //return $form;
    drupal_exit();
}