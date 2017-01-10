<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Шапка
 */
function set_roundprokat_page(){
    $output = '';
    //$output .= render(drupal_get_form('calcmet_undercat_form'));
    $output .= render(drupal_get_form('calcmet_roundprokat_form'));
    $output .= render(drupal_get_form('roundprokat_spec_form'));
    //$output .= '</div>';
    return $output;
}
/*function calcmet_undercat_form($form, &$form_state){
    $form['cat'] = array(
        '#title' => t('Категория проката'),
        '#type' => 'select',
        '#options' => calcmet_get_undercategory_title('calcmetundercat'),
        '#default_value' => 5,
        //'#size' => 10,
        '#description' => t('Выберите тип стального проката'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'roundprokat_change_cat',
//        ),
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>'  
    );
    $form_state['rebuild'] = TRUE;
    return $form;
}*/

/*
    Раздел по квадрату
 */
function calcmet_roundprokat_form($form, &$form_state){
    $form = array();
    
    $form['roundprokat'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['roundprokat']['roundprokatnames'] = array(
        '#title' => t('Диаметр, мм'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetprutok'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип проката'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'roundprokat_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['roundprokat']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'roundprokat_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['roundprokat']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['roundprokat']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['roundprokat']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/roundprokat.jpg" width=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['roundprokat']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="roundprokat-info">'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">0.196</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.154</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 2590-2006 "Прокат сортовой стальной горячекатаный круглый. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 30.01.2007 № 4'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['roundprokat']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetroundprokat.js',
    );
    $form['#action'] = url('/services/calcmet/roundprokat');
    $form_state['rebuild'] = TRUE;
    return $form;
}


function roundprokat_spec_form($form, &$form_state){
    $form['spec'] = array(
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
    return $form;
}

function roundprokat_change_info(){
    $select = $_POST['option'];
    $basename = $_POST['roundprokatname'];
    //dsm($select);
    switch ($basename) {
        case 'roundprokat':
            $infos = db_select('calcmetprutok', 'p')
                ->fields('p', array('prutokdiametr','prutokcsa', 'prutokmassonem',))
                ->condition('p.prutokdid', $select)
                ->execute()
                ->fetchAll();
            $diametr = $infos[0]->prutokdiametr;
            $csatext = $infos[0]->prutokcsa;
            $massonem = $infos[0]->prutokmassonem;
            $csa = $diametr*3.14*0.001;
        break;

        default:
        break;
    }
    drupal_json_output(array(                       
                //'diametr'=> $diametr,                                                                  
                'csatext'=> $csatext,                       
                'csa'=> $csa,                       
                'massonem'=> $massonem,                       
                ));       
    drupal_exit();
}

/*function calcmet_get_undercategory_title($basename){
     $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetundercat':
                if ($entry->ccid == 7){
                    $options[$entry->cucid] = $entry->title;
                }
                break;
            default:
                break;
        }
    }
    return $options;
}*/

function calcmet_get_options ($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetprutok':
                $options[$entry->prutokdid] = $entry->prutokdiametr;
                break;
            default:
                break;
        }
    }
    return $options;
}

/*function roundprokat_change_options(){
    $select = $_POST['ajaxroundprokatchangeoptions'];
    switch ($select) {
            case 5:
                $form = drupal_render(drupal_get_form('calcmet_roundprokat_bezshov_form'));                
                break;
            case 6:
                $form = drupal_render(drupal_get_form('calcmet_roundprokat_form'));
                break;
            case 7:
                $form = drupal_render(drupal_get_form('calcmet_roundprokat_kvadrat_form'));
                break;
            case 8:
                $form = drupal_render(drupal_get_form('calcmet_roundprokat_oval_form'));
                break;
            case 9:
                $form = drupal_render(drupal_get_form('calcmet_roundprokat_ugol_form'));
                break;

            default:
                break;
        }
    drupal_json_output($form);
    //return $form;
    drupal_exit();
}*/